#include <string>
#include <iostream>

#include "webrtc/modules/audio_processing/include/audio_processing.h"
#include "webrtc/modules/interface/module_common_types.h"

using webrtc::AudioProcessing;
using webrtc::AudioFrame;
using webrtc::GainControl;
using webrtc::NoiseSuppression;
using webrtc::EchoCancellation;
#define EXPECT_OP(op, val1, val2)                                       \
  do {                                                                  \
    if (!((val1) op (val2))) {                                          \
      fprintf(stderr, "Check failed: %s %s %s\n", #val1, #op, #val2);   \
      exit(1);                                                          \
    }                                                                   \
  } while (0)

#define EXPECT_EQ(val1, val2)  EXPECT_OP(==, val1, val2)
#define EXPECT_NE(val1, val2)  EXPECT_OP(!=, val1, val2)
#define EXPECT_GT(val1, val2)  EXPECT_OP(>, val1, val2)
#define EXPECT_LT(val1, val2)  EXPECT_OP(<, val1, val2)

int usage() {
    std::cout <<
              "Usage: audio_test_main -anc|-agc|-aec value input.raw output.raw [delay_ms echo_in.raw]"
              << std::endl;
    return 1;
}

bool ReadFrame(FILE* file, webrtc::AudioFrame* frame) {
    // The files always contain stereo audio.
    size_t frame_size = frame->samples_per_channel_;
    size_t read_count = fread(frame->data_,
                              sizeof(int16_t),
                              frame_size,
                              file);
    if (read_count != frame_size) {
        // Check that the file really ended.
        EXPECT_NE(0, feof(file));
        return false;  // This is expected.
    }
    return true;
}

bool WriteFrame(FILE* file, webrtc::AudioFrame* frame) {
    // The files always contain stereo audio.
    size_t frame_size = frame->samples_per_channel_;
    size_t read_count = fwrite (frame->data_,
                                sizeof(int16_t),
                                frame_size,
                                file);
    if (read_count != frame_size) {
        return false;  // This is expected.
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc != 5 && argc != 7) {
        return usage();
    }

    bool is_echo_cancel = false;
    FILE *echo_in = NULL;
    int level, delay_ms = -1;
    level = atoi(argv[2]);

    // Usage example, omitting error checking:
    webrtc::AudioProcessing* apm = webrtc::AudioProcessing::Create();
    apm->high_pass_filter()->Enable(true);
    if (std::string(argv[1]) == "-anc") {
        std::cout << "ANC: level " << level << std::endl;
        switch (level) {
        case 0:
            apm->noise_suppression()->set_level(webrtc::NoiseSuppression::kLow);
            break;
        case 1:
            apm->noise_suppression()->set_level(webrtc::NoiseSuppression::kModerate);
            break;
        case 2:
            apm->noise_suppression()->set_level(webrtc::NoiseSuppression::kHigh);
            break;
        case 3:
            apm->noise_suppression()->set_level(webrtc::NoiseSuppression::kVeryHigh);
            break;
        default:
            apm->noise_suppression()->set_level(webrtc::NoiseSuppression::kVeryHigh);
        }
        apm->noise_suppression()->Enable(true);
        //apm->voice_detection()->Enable(true);
    } else if (std::string(argv[1]) == "-agc") {
        std::cout << "AGC mode : AdaptiveDigital, " << " Level = " << level << std::endl;
        //std::cout << "AGC mode : AdaptiveAnalog" << level << std::endl;
        apm->gain_control()->set_analog_level_limits(0, 255);
        apm->gain_control()->set_mode(webrtc::GainControl::kAdaptiveDigital);
        //apm->gain_control()->set_mode(webrtc::GainControl::kAdaptiveAnalog);
        //Default Gain control mode is kAdaptiveAnalog, so if mode is not set, 
        //that means kAdaptiveAnalog is being used.
        
        apm->gain_control()->Enable(true);        
    } else if (std::string(argv[1]) == "-aec") {
        webrtc::EchoCancellation *echo_cancell = apm->echo_cancellation();
        is_echo_cancel = true;
        echo_cancell->enable_drift_compensation(false);
        std::cout << "AEC: level " << level << std::endl;
        switch (level) {
            case 0:
                echo_cancell->set_suppression_level(webrtc::EchoCancellation::kLowSuppression);
                break;
            case 1:
                echo_cancell->set_suppression_level(webrtc::EchoCancellation::kModerateSuppression);
                break;
            case 2:
                echo_cancell->set_suppression_level(webrtc::EchoCancellation::kHighSuppression);
        }
        delay_ms = atoi(argv[5]);
        //apm->set_stream_delay_ms(delay_ms);
        EXPECT_NE(echo_in = fopen(argv[6], "rb"), NULL);
        echo_cancell->Enable(true);        
    } else {
        delete apm;
        return usage();
    }

    //apm->Initialize();



    webrtc::AudioFrame *frame = new webrtc::AudioFrame();
    float frame_step = 10;  // ms
    frame->sample_rate_hz_ = 8000; //16000;
    frame->samples_per_channel_ = frame->sample_rate_hz_ * frame_step / 1000.0;

    frame->num_channels_ = 1;
    webrtc::AudioFrame *echo_frame = NULL;
    if (is_echo_cancel) {
        echo_frame = new webrtc::AudioFrame();
        echo_frame->sample_rate_hz_ = 8000;//16000;
        echo_frame->samples_per_channel_ = echo_frame->sample_rate_hz_ * frame_step / 1000.0;

        echo_frame->num_channels_ = 1;        
    }

    FILE *wav_in = fopen(argv[3], "rb");
    FILE *wav_out = fopen(argv[4], "wb");
    EXPECT_NE(wav_in, NULL);
    EXPECT_NE(wav_out, NULL);
    int num_frame = 0;
    while (ReadFrame(wav_in, frame)) {
        num_frame += 1;
        if (is_echo_cancel) {
            if (ReadFrame(echo_in, echo_frame)) {
                apm->ProcessReverseStream(echo_frame);
                apm->set_stream_delay_ms(40);//apm->set_stream_delay_ms(0);
            }
        }        
        if(apm->gain_control()->is_enabled()) {
            //apm->gain_control()->set_stream_analog_level(level);
            //apm->gain_control()->set_target_level_dbfs(level);
        }
        apm->ProcessStream(frame);
        WriteFrame(wav_out, frame);
    }

    int analog_level = 0;

    if((apm->gain_control()->is_enabled()) && ( webrtc::GainControl::kAdaptiveAnalog == apm->gain_control()->mode())) {
        apm->gain_control()->stream_analog_level();
        std::cout << "analog_level = " << analog_level << std::endl;
    }

    fclose(wav_in);
    fclose(wav_out);
    if(is_echo_cancel && echo_in)
        fclose(echo_in);

    if(frame)
    {
        delete frame;
        frame = NULL;
    }
    if (is_echo_cancel)
        delete echo_frame;

    if(apm)
    {
        delete apm;
        apm = NULL;
    }

    return 0;
}
