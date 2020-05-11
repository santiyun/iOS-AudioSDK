## 纯音频SDK

纯音频SDK使用需要同时下载依赖库[TTTPlayerKit.framework](https://github.com/santiyun/TTTPlayerKit_iOS)

更新纯音频SDK时不需要更新**TTTPlayerKit.framework**

如果项目中使用了IJK拉流的库可去掉**TTTPlayerKit.framework**，去掉拉流库出现问题请联系我们

## Pod说明

纯音频SDK：**TTTRtcEngineVoiceKit_iOS** 

拉流SDK：**TTTPlayerKit_iOS** 

如果pod search不到，请更新Pod环境


## 2.9.2

1. 优化PK流程



## 2.9.1

1. **TTTPublisherConfiguration.videoSize** 参数过期
2. **TTTPublisherConfiguration.bitrate** 参数去掉
3. **TTTPublisherConfiguration.encoderMode** 智感超清编码
4. **TTTRtcVideoProfile** 部分分辨率的帧率，码率调整
5. 去掉XML解析库

## 2.8.0

1. 新增启用默认音频播放功能**enableDefaultAudioPaly**
2. 优化退房间资源释放

## 2.7.3

#### 修改

1. 优化部分功能

## 2.7.1

#### 修改

1. 修改内部日志

## 2.7.0

#### 修改

1. 优化断网重连
2. 优化直播推流配置**TTTPublisherConfiguration**

## 2.6.0

1. 修复已知bug
2. 优化网络传输

## 2.5.0

#### 新增

1. 增加**adjustPlaybackSignalVolume:**调节播放人声的音量
2. 增加**muteRemoteRtmpAudioStream**停止/恢复远端用户音频混流到rtmp

#### 修改

1. **TTTRtcLocalAudioStats**增加**rtt**属性
2. **TTTRtcRemoteAudioStats**增加**rtt**属性
3. 网络传输优化

## 2.4.0

#### 新增方法

1. 增加**stopAudioPlayAndRecord**停止/恢复音频采集和播放
2. 增加**setRecordingAudioFrameParametersWithSampleRate**设置录制的声音格式
3. 增加**setPlaybackAudioFrameParametersWithSampleRate**设置播放的声音格式
4. 增加**setMixedAudioFrameParametersWithSampleRate**设置录制和播放声音混音后的数据格式
5. 增加**sendAudioLyric**发送歌词

#### 新增回调

1. **receiveAudioLyricOfUid** 接收远端用户发来的歌词
2. **mixAudioData** 混音音频数据回调


## 2.3.0


#### 新增方法

1. 增加**setAudioEarBackVolume**设置耳返音量的方法
2. 增加**adjustAudioMixingPlayoutVolume**调节伴奏本地播放音量
3. 增加**adjustAudioMixingPublishVolume**调节伴奏远端播放音量
4. 增加网络连接状态相关接口

 > **getConnectionState**获取网络状态

 > **connectionChangedToState**网络连接状态发生改变回调

 > **TTTConnectionState**网络状态枚举


5. 增加客户端录音相关方法

 > **startAudioRecording** 开始客户端录音

 > **stopAudioRecording** 停止客户端录音

 > **TTTAudioRecordQuality** 录音音质枚举

6. 增加外置音频源相关方法

 > **setExternalAudioSource** 配置外部音频源

 > **pushExternalAudioFrame** 推送外部音频采集数据

 > **pullRenderingAudioFrame** 拉取音频播放数据
 
#### 过期方法

1. **adjustAudioMixingVolume**
