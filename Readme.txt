From PulseAudio : http://freedesktop.org/software/pulseaudio/webrtc-audio-processing/


1. 执行./autogen.sh，通过automake工具生成configure文件， Makefile文件。
2. 执行./configure --prefix=/some/local/path做相关的配置，指定文件的生成目录。
3. 执行make。
4. 执行make install
5. 更多信息，请参考项目下的Readme, Makefile等配置文件。重点是UPDATING.md