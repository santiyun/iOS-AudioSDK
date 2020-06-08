#import <Foundation/Foundation.h>
#import "TTTRtcEngineDelegate.h"
#import "TTTVoiceEnumerates.h"
#import "TTTVoiceObjects.h"

@interface TTTRtcEngineKit : NSObject

/** 应用ID，由连麦平台分配，用于区分不同的客户和应用 */
@property (nonatomic, copy) NSString *appID;

/**  SDK回调对象，由调用方赋值 */
@property (nonatomic, weak) id<TTTRtcEngineDelegate> delegate;

/** 音视频信息统计间隔（默认：2秒） */
@property (nonatomic, assign) NSUInteger statsInterval;

#if TARGET_OS_OSX

/** 音频采集设备 */
@property (nonatomic, weak) TTTRtcAudioDevice *audioCaptureDevice;

/** 音频输出设备 */
@property (nonatomic, weak) TTTRtcAudioDevice *audioPlayoutDevice;

#endif

/**
 *  初始化SDK，加载资源。
 *
 *  @param appId        应用ID，由连麦平台分配，用于区分不同的客户和应用，在同一个连麦平台内保证唯一。
    可以通过([TTTRtcEngineKit.appID])设置新的appID
 *
 *  @param delegate     SDK回调代理, 可以通过([TTTRtcEngineKit.delegate])设置新的代理
 *
 *  @return TTTRtc 对象(单例)
 */
+ (instancetype)sharedEngineWithAppId:(NSString *)appId delegate:(id<TTTRtcEngineDelegate>)delegate;

/**
 *  销毁引擎实例
 */
+ (void)destroy;

/**
 *  获取SDK版本号
 */
+ (NSString *)getSdkVersion;

/**
 *  设置服务器地址
 *
 *  @param ip   ip地址或域名
 *  @param port 端口
 */
- (void)setServerIp:(NSString*)ip port:(int)port;

/**
 *  设置频道模式
 *  加入房间之前设置，在房间内不能做修改。设置该方法之后再设置角色([TTTRtcEngineKit setClientRole:])
 *
 *  @param profile 频道模式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setChannelProfile:(TTTRtcChannelProfile)profile;

/**
 *  设置或切换用户角色
 *  加入房间前要确定用户角色，在加入房间的过程中不能修改角色。
 *  加入房间成功之后，副播和观众可以相互切换，角色切换成功之后才能进行下一次切换，切换角色成功的回调 ([TTTRtcEngineDelegate rtcEngine:didClientRoleChangedOfUid:role:])。
 *  切换角色SDK会对用户的音频权限做对应调整，不需要调用额外接口
 *
 *  @param role          直播场景里的用户角色
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setClientRole:(TTTRtcClientRole)role;

/**
 *  加入通话频道
 *
 *  @param channelKey        此为程序生成的ChannelKey(token), 用于SDK鉴权
 *  @param channelName       标识通话的频道名称，使用可转换大于0的long long类型纯数字字符串
 *  @param uid               用户ID
 *  @param joinSuccessBlock  用户加入成功回调, 优先级高于([TTTRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]), 实现block, 回调不会被调用
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)joinChannelByKey:(NSString *)channelKey
            channelName:(NSString *)channelName
                    uid:(int64_t)uid
            joinSuccess:(void(^)(NSString *channel, int64_t uid, NSInteger elapsed))joinSuccessBlock;

/**
 *  离开房间
 *
 *  @param leaveChannelBlock 成功离开房间的回调，优先级高于([TTTRtcEngineDelegate rtcEngine:didLeaveChannelWithStats:]), 实现block, 回调不会被调用
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)leaveChannel:(void(^)(TTTRtcStats *stats))leaveChannelBlock;

/**
 *  更新channelKey
 *  当房间内的channelKey(token)即将过期([TTTRtcEngineDelegate rtcEngine:channelKeyPrivilegeWillExpire:])
 *  通过该方法更新新的channelKey(token), 更新失败([TTTRtcEngineDelegate rtcEngine:didOccurError:])(TTTRtc_Error_InvalidChannelKey)
 *
 *  @param channelKey 此为程序生成的ChannelKey(token)
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)renewChannelByKey:(NSString *)channelKey;

/**
 * 获取网络连接状态
 */
- (TTTConnectionState)getConnectionState;

/**
 *  静音/取消静音
 *  允许/禁止往网络发送本地音频流。
 *
 *  @param mute YES: 麦克风静音, NO: 取消静音。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteLocalAudioStream:(BOOL)mute;

/**
 *  调节本地说话音量
 *
 *  @param volume 音量范围为0~500。默认100为原始音量
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustAudioMixingSoloVolume:(NSInteger)volume;

/**
 *  调节播放人声的音量
 *
 *  @param volume 音量范围为0~500。默认100为原始音量
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;

/**
 *  静音所有远端音频/对所有远端音频取消静音
 *  允许/禁止播放远端用户的音频流，即对所有远端用户进行静音与否。
 *
 *  @param mute YES: 停止播放所接收的音频流, NO: 恢复播放所接收的音频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/**
 *  静音指定远端用户/对指定远端用户取消静音
 *  允许/禁止播放远端用户的音频流。
 *
 *  @param mute YES: 停止播放指定用户的音频流, NO: 恢复播放指定用户的音频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteAudioStream:(int64_t)uid mute:(BOOL)mute;

/**
 *  禁言指定远端用户/对指定远端用户取消禁言
 *  仅直播模式下，主播具有该权限
 *
 *  @param mute YES: 禁止发言, NO: 允许发言。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteSpeaking:(int64_t)uid mute:(BOOL)mute;

/**
 *  停止/恢复远端用户音频混流到rtmp
 *
 *  @param uid     用户ID
 *  @param mute    YES: 停止混音频流, NO: 恢复混音频流。
 *  @param rtmpUrl rtmp推流地址, 推单路流可设置为nil
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteRtmpAudioStream:(int64_t)uid mute:(BOOL)mute rtmpUrl:(NSString *)rtmpUrl;

/**
 * 启用/禁用回声消除
 * 加入房间之后调用，默认启用
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableHWAEC:(BOOL)enable;

/**
 * 启用/禁用软件回声消除
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableSoftAEC:(BOOL)enable;

/**
 * 启用/禁用音频降噪
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableDenoise:(BOOL)enable;

/**
 *  打开/关闭耳返功能
 *  在插入耳机的情况下有效
 *
 *  @param enable YES: 打开耳返功能，NO: 关闭耳返功能。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioEarBack:(BOOL)enable;

/**
 *  设置耳返音量
 *  在打开耳返的情况下有效
 *
 *  @param volume 设置耳返音量，取值范围在 [0,100] 默认值为 100
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setAudioEarBackVolume:(NSUInteger)volume;

/**
 *  是否打开耳返
 *
 *  @return YES: 耳返是打开状态，NO: 耳返是关闭状态。
 */
- (BOOL)isAudioEarBackEnabled;

/**
 *  启用/关闭本地音频和远端音频数据回调
 *  本地音频裸数据回调([TTTRtcEngineDelegate rtcEngine:localAudioData:dataSize:sampleRate:channels:])
 *  远端用户混音数据回调([TTTRtcEngineDelegate rtcEngine:remoteAudioData:dataSize:sampleRate:channels:])
 *
 *  @param enableLocal YES: 获取本地音频数据，NO: 关闭获取本地音频数据。
 *
 *  @param enableRemote YES: 获取远端音频数据，NO: 关闭获取远端音频数据。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioDataReport:(BOOL)enableLocal remote:(BOOL)enableRemote;

#if TARGET_OS_IOS

/**
 *  切换音频路由
 *  在插入耳机或蓝牙耳机状态下，不建议调用该接口
 *
 *  @param enableSpeaker YES: 音频输出至扬声器，NO: 语音会根据默认路由出声。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/**
 *  是否是扬声器状态
 *
 *  @return YES: 表明输出到扬声器，NO: 表明输出到非扬声器(听筒，耳机等)。
 */
- (BOOL)isSpeakerphoneEnabled;

/**
 *  设置默认的语音路由
 *
 *  @param defaultToSpeaker YES: 从扬声器出声，NO: 从听筒出声
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setDefaultAudioRouteToSpeakerphone:(BOOL)defaultToSpeaker;

#endif

/**
 *  启用说话者音量提示
 *  音量回调([TTTRtcEngineDelegate rtcEngine:reportAudioLevel:audioLevel:audioLevelFullRange:])
 *
 *  @param interval 指定音量提示的时间间隔（<=0: 禁用音量提示功能；>0: 提示间隔，单位为毫秒。建议设置到大于200毫秒。）
 *  @param smooth   平滑系数。默认可以设置为3。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval smooth:(NSInteger)smooth;

/**
 *  设置日志文件
 *  正式发版或上线不建议设置该路径，有需求的用户需要管理日志文件
 *
 *  @param filePath 日志文件的完整路径。该日志文件为UTF-8编码。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setLogFile:(NSString *)filePath;

/**
 *  设置日志文件过滤器
 *
 *  @param filter 日志过滤器
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setLogFilter:(TTTRtcLogFilter)filter;

/**
 *  往日志文件中增加自定义日志
 *  进入房间后才可使用
 *
 *  @param log 日志内容
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)addLog:(NSString *)log;

/**
 *  设置信令超时时间
 *  默认90s, 设置时长需要大于20s
 *
 *  @param seconds 超时时间（秒）
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setSignalTimeout:(NSUInteger)seconds;

/**
 *  设置音频编码选项
 *
 *  @param codecType 音频编码格式
 *  @param bitrate   码率
 *  @param channels  声道
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setPreferAudioCodec:(TTTRtcAudioCodecType)codecType bitrate:(int)bitrate channels:(int)channels;

/**
 *  开始客户端本地混音
 *  默认仅支持mp3格式音乐文件
 *  对于播放通话开始或结束提示音，可以使用该接口，结束需要调用([TTTRtcEngineKit stopAudioMixing])
 *  播放开始([TTTRtcEngineDelegate rtcEngineAudioMixingDidStart:])
 *  播放结束([TTTRtcEngineDelegate rtcEngineAudioMixingDidFinish:])
 *
 *  @param filePath 指定需要混音的本地音频文件名和文件路径
 *  @param loopback YES: 只有本地可以听到混音后的音频流，NO: 本地和对方都可以听到混音后的音频流。
 *  @param cycle    指定音频文件循环播放的次数, 0:无限循环
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startAudioMixing:(NSString *)filePath loopback:(BOOL)loopback cycle:(NSInteger)cycle;

/**
 *  停止客户端本地混音
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopAudioMixing;

/**
 *  暂停播放伴奏
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)pauseAudioMixing;

/**
 *  恢复播放伴奏
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)resumeAudioMixing;

/**
 *  调节伴奏本地播放音量
 *
 *  @param volume 伴奏音量范围为0~100。默认100为原始文件音量。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustAudioMixingPlayoutVolume:(NSUInteger)volume;

/**
 *  调节伴奏远端播放音量
 *
 *  @param volume 伴奏音量范围为0~100。默认100为原始文件音量。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustAudioMixingPublishVolume:(NSUInteger)volume;

/**
 *  获取伴奏时长
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)getAudioMixingDuration;

/**
 *  获取伴奏播放进度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)getAudioMixingCurrentPosition;

/**
 *  拖动语音进度条
 *
 *  @param pos 进度条位置，单位为毫秒。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setAudioMixingPosition:(NSInteger)pos;

#pragma mark - 音效接口
- (double)getEffectsVolume;//0~1
- (int)setEffectsVolume:(double)volume;
- (int)setVolumeOfEffect:(int)soundId withVolume:(double)volume;
- (int)playEffect:(int)soundId filePath:(NSString *)filePath loopCount:(int)loopCount pitch:(double)pitch pan:(double)pan gain:(double)gain publish:(BOOL)publish;
- (int)stopEffect:(int)soundId;
- (int)stopAllEffects;
- (int)preloadEffect:(int)soundId filePath:(NSString *)filePath;
- (int)unloadEffect:(int)soundId;
- (int)pauseEffect:(int)soundId;
- (int)pauseAllEffects;
- (int)resumeEffect:(int)soundId;
- (int)resumeAllEffects;

/**
 *  踢出房间
 *  直播模式(TTTRtc_ClientRole_Anchor)调用有效
 *
 *  @param uid 被踢者uid
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)kickChannelUser:(int64_t)uid;

/**
 *  配置旁路直播推流
 *
 *  @param config 直播推流配置
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)configPublisher:(TTTPublisherConfiguration *)config;

/**
 *  开启网络质量检测
 *  对应回调([TTTRtcEngineDelegate rtcEngine:lastmileQuality:])
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableLastmileTest;

/**
 *  关闭网络质量检测
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)disableLastmileTest;

/**
 *  开始客户端录音
 *
 *  @param filePath 录音文件的本地保存路径: xxx/.../xxx.aac
 *  @param quality  录音质量
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startAudioRecording:(NSString *)filePath quality:(TTTAudioRecordQuality)quality;

/**
 *  停止客户端录音
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopAudioRecording;

/**
 *  配置外部音频源
 *  在加入房间之前开启, 开启该功能需要同时做采集和播放。
 *  音频路由相关需要开发者自己控制
 *
 *  @param enable      是否启用外部音频源
 *  @param sampleRate  外部音频源的采样率
 *  @param channels    外部音频源的通道数
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setExternalAudioSource:(BOOL)enable sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  推送外部音频采集数据
 *
 *  @param data        PCM数据
 *  @param len         PCM数据长度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)pushExternalAudioFrame:(int8_t *)data length:(int)len;

/**
 *  拉取音频播放数据
 *  外置音频源前提下，拉取用于渲染的数据
 *
 *  @param data        PCM数据
 *  @param len         PCM数据长度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)pullRenderingAudioFrame:(int8_t *)data length:(int)len;

/**
 *  停止/恢复音频采集和播放
 *
 *  @param stop  YES: 停止采集和播放  NO: 恢复采集和播放
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopAudioPlayAndRecord:(BOOL)stop;

/**
 *  设置录制的声音格式
 *  回调([TTTRtcEngineDelegate rtcEngine:localAudioData:dataSize:sampleRate:channels:])
 *  如果只需要本地采集音频裸数据可以使用([TTTRtcEngineKit enableAudioDataReport:remote:])
 *
 *  @param sampleRate     采样率，建议设置为AVAudioSession.sharedInstance.sampleRate
 *  @param channel        声道数，可设置：1或2
 *  @param samplesPerCall 采样点数，建议设置：1024或2048
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setRecordingAudioFrameParametersWithSampleRate:(NSInteger)sampleRate channel:(NSInteger)channel samplesPerCall:(NSInteger)samplesPerCall;

/**
 *  设置播放的声音格式
 *  回调([TTTRtcEngineDelegate rtcEngine:remoteAudioData:dataSize:sampleRate:channels:])
 *  如果只需要远端用户音频裸数据可以使用([TTTRtcEngineKit enableAudioDataReport:remote:])
 *
 *  @param sampleRate     采样率，建议设置为AVAudioSession.sharedInstance.sampleRate
 *  @param channel        声道数，可设置：1或2
 *  @param samplesPerCall 采样点数，建议设置：1024或2048
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setPlaybackAudioFrameParametersWithSampleRate:(NSInteger)sampleRate channel:(NSInteger)channel samplesPerCall:(NSInteger)samplesPerCall;

/**
 *  设置录制和播放声音混音后的数据格式
 *  回调([TTTRtcEngineDelegate rtcEngine:mixAudioData:dataSize:sampleRate:channels:])
 *
 *  @param sampleRate     采样率
 *  @param channel        声道数，可设置：1或2
 *  @param samplesPerCall 采样点数，建议设置：1024或2048
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setMixedAudioFrameParametersWithSampleRate:(NSInteger)sampleRate channel:(NSInteger)channel samplesPerCall:(NSInteger)samplesPerCall;

/**
 *  启用默认音频播放
 *  调用该功能，内部会播放默认静音数据
 *
 *  @param enable  是否启用默认播放
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableDefaultAudioPaly:(BOOL)enable;

/**
 *  发送歌词
 *
 *  @param lyric 歌词内容
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)sendAudioLyric:(NSString *)lyric;

@end

