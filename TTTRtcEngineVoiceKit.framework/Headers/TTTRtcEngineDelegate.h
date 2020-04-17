//
//  TTTRtcEngineDelegate.h
//  TTTRtcEngineKit
//
//  Created by Work on 2020/2/17.
//  Copyright © 2020 PView. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TTTVoiceEnumerates.h"
#import "TTTVoiceObjects.h"

/**
 *  SDK回调代理，由调用方实现。
 */
@class TTTRtcEngineKit;
@protocol TTTRtcEngineDelegate <NSObject>

@optional

/**
 *  发生错误回调
 *  通常情况下，SDK上报的错误意味着SDK无法自动恢复，需要应用程序干预或提示用户。
 *
 *  @param errorCode 错误代码
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didOccurError:(TTTRtcErrorCode)errorCode;

/**
 *  网络连接丢失回调, 提示用户网络异常。
 *  SDK会自动重连，重连失败([TTTRtcEngineDelegate rtcEngineReconnectServerTimeout:])
 *  重连成功([TTTRtcEngineDelegate rtcEngineReconnectServerSucceed:])
 */
- (void)rtcEngineConnectionDidLost:(TTTRtcEngineKit *)engine;

/**
 *  网络重连失败
 *  网络异常断开后，将尝试重连, 默认90s, 可通过([TTTRtcEngineKit setSignalTimeout:])设置
 *  在重连时间范围内无法连接上服务器触发该回调，需要调用([TTTRtcEngineKit leaveChannel:])
 *  若在重连时间范围外才重连上服务器，服务器将会拒绝，其房间状态将不可用。
 */
- (void)rtcEngineReconnectServerTimeout:(TTTRtcEngineKit *)engine;

/**
 *  重连成功
 *  重连成功之后SDK所有状态恢复
 */
- (void)rtcEngineReconnectServerSucceed:(TTTRtcEngineKit *)engine;

/**
 *  网络连接状态发生改变
 *  也可使用([TTTRtcEngineKit getConnectionState])获取SDK网络连接状态
 *
 *  @param state 当前网络连接状态
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine connectionChangedToState:(TTTConnectionState)state;

/**
 *  加入频道成功回调
 *
 *  @param channel 频道名
 *  @param uid     用户ID
 *  @param elapsed 从joinChannel开始到该事件产生的延迟（毫秒）
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didJoinChannel:(NSString*)channel withUid:(int64_t)uid elapsed:(NSInteger)elapsed;

/**
 *  成功离开频道的回调
 *  调用([TTTRtcEngineKit leaveChannel:])即认为离开房间，不需要等待回调
 *
 *  @param stats 统计数据
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didLeaveChannelWithStats:(TTTRtcStats *)stats;

/**
 *  用户加入回调
 *
 *  @param uid            用户ID
 *  @param clientRole     用户角色
 *  @param isVideoEnabled 是否启用本地视频
 *  @param elapsed        加入频道开始到该回调触发的延迟（毫秒)
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didJoinedOfUid:(int64_t)uid clientRole:(TTTRtcClientRole)clientRole
    isVideoEnabled:(BOOL)isVideoEnabled elapsed:(NSInteger)elapsed;

/**
 *  用户离线回调
 *
 *  @param uid    用户ID
 *  @param reason 离线原因
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didOfflineOfUid:(int64_t)uid reason:(TTTRtcUserOfflineReason)reason;

/**
 *  用户被踢出回调
 *
 *  @param uid    用户ID
 *  @param reason 用户被踢出的原因
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didKickedOutOfUid:(int64_t)uid reason:(TTTRtcKickedOutReason)reason;

/**
 *  用户角色切换回调
 *
 *  @param uid  用户ID
 *  @param role 用户角色
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didClientRoleChangedOfUid:(int64_t)uid role:(TTTRtcClientRole)role;

/**
 *  禁止/允许用户发言回调
 *
 *  @param muted YES: 禁止发言，NO: 允许发言。
 *  @param uid   用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didSpeakingMuted:(BOOL)muted ofUid:(int64_t)uid;

/**
 *  用户音频静音回调
 *
 *  @param muted YES: 静音，NO: 取消静音。
 *  @param uid   用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didAudioMuted:(BOOL)muted byUid:(int64_t)uid;

/**
 *  音频输出路由发生变化
 *
 *  @param routing 当前音频输出路由
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didAudioRouteChanged:(TTTRtcAudioOutputRouting)routing;

/**
 *  RtcEngine统计数据回调
 *
 *  @param stats 通话相关的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine reportRtcStats:(TTTRtcStats *)stats;

/**
 *  本地音频统计回调
 *
 *  @param stats 本地音频的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine localAudioStats:(TTTRtcLocalAudioStats *)stats;

/**
 *  远端音频统计回调
 *
 *  @param stats 远端音频的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine remoteAudioStats:(TTTRtcRemoteAudioStats *)stats;

/**
 *  远端用户音量回调
 *  提示谁在说话及其音量，默认禁用。
 *  可通过([TTTRtcEngineKit enableAudioVolumeIndication:smooth:])方法设置。
 *
 *  @param uid                 用户ID
 *  @param audioLevel          非线性区间[0,9]
 *  @param audioLevelFullRange 线性区间[0,32768]
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine reportAudioLevel:(int64_t)uid
       audioLevel:(NSUInteger)audioLevel audioLevelFullRange:(NSUInteger)audioLevelFullRange;

/**
 *  远端首次音频数据接收回调
 *
 *  @param uid     用户ID，指定是哪个用户的音频数据
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstRemoteAudioDataIncommingOfUid:(int64_t)uid;

/**
 *  远端音频第一帧解码回调
 *
 *  @param uid 用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstAudioFrameDecoded:(int64_t)uid;



/**
 *  本端音频采集数据回调
 *
 *  @param data        PCM数据
 *  @param size        PCM数据长度
 *  @param sampleRate  采样率
 *  @param channels    声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine localAudioData:(char *)data dataSize:(NSUInteger)size sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  远端音频数据回调
 *
 *  @param data        音频数据
 *  @param size        数据长度
 *  @param sampleRate  采样率
 *  @param channels    声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine remoteAudioData:(char *)data dataSize:(NSUInteger)size sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  混音音频数据回调
 *  通过[([TTTRtcEngineKit setMixedAudioFrameParametersWithSampleRate:channel:samplesPerCall:])启用
 *
 *  @param data        音频数据
 *  @param size        数据长度
 *  @param sampleRate  采样率
 *  @param channels    声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine mixAudioData:(char *)data dataSize:(NSUInteger)size sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  伴奏播放开始的回调
 */
- (void)rtcEngineAudioMixingDidStart:(TTTRtcEngineKit *)engine;

/**
 *  伴奏播放完成的回调
 */
- (void)rtcEngineAudioMixingDidFinish:(TTTRtcEngineKit *)engine;

/**
 *  音效播放完成的回调
 */
- (void)rtcEngineDidAudioEffectFinish:(TTTRtcEngineKit *)engine soundId:(NSInteger)soundId;

- (void)rtcEngineOnMediaSending:(TTTRtcEngineKit *)engine;

/**
 *  网络质量检测回调
 *  调用([TTTRtcEngineKit enableLastmileTest])开启
 *
 *  @param quality 网络质量
 *
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine lastmileQuality:(TTTNetworkQuality)quality;

/**
 *  channelKey即将过期
 *  时间距即将过期10~60s, 取channelKe有效时间的1/6，大于60s按照60s计算
 *  收到回调时，可以([TTTRtcEngineKit renewChannelByKey:])更新新的channelKey
 *
 *  @param channelKey token
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine channelKeyPrivilegeWillExpire:(NSString *)channelKey;

/**
 *  外部音频混音
 *
 *  @param data        混音的数据
 *  @param size        混音的音频数据长度
 *  @param sampleRate  混音的采样率
 *  @param channels    混音数据声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine pullAudioData:(char *)data size:(int)size sampleRate:(NSUInteger)sampleRate channels:(int)channels;

/**
 *  接收远端用户发来的歌词
 *
 *  @param uid   用户id
 *  @param lyric 歌词内容
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine receiveAudioLyricOfUid:(int64_t)uid lyric:(NSString *)lyric;
@end
