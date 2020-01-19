//
//  TTTVoiceEnumerates.h
//  TTTRtcEngineVoiceKit
//
//  Created by yanzhen on 2020/1/3.
//  Copyright © 2020 TTT. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  错误代码
 */
typedef NS_ENUM(NSUInteger, TTTRtcErrorCode) {
    TTTRtc_Error_NoError             = 0,    // 没有错误
    // 进入房间错误
    TTTRtc_Error_InvalidChannelName  = 9000, // 无效的房间名称
    TTTRtc_Error_Enter_TimeOut       = 9001, // 超时,10秒未收到服务器返回结果
    TTTRtc_Error_Enter_Failed        = 9002, // 无法连接服务器
    TTTRtc_Error_Enter_VerifyFailed  = 9003, // 验证码错误
    TTTRtc_Error_Enter_BadVersion    = 9004, // 版本错误
    TTTRtc_Error_Enter_Unknown       = 9005, // 未知错误
    TTTRtc_Error_Enter_NoAnchor      = 9006, // 房间内没有主播
    TTTRtc_Error_NoAudioData         = 9101, // 长时间没有上行音频数据
    TTTRtc_Error_NoReceivedAudioData = 9111, // 长时间没有下行音频数据
    TTTRtc_Error_InvalidChannelKey   = 9200, //无效的channelKey
    TTTRtc_Error_Unknown             = 9999, // 未知错误
};

/**
 *  踢出房间原因
 */
typedef NS_ENUM(NSUInteger, TTTRtcKickedOutReason) {
    TTTRtc_KickedOut_KickedByHost      = 1, // 被主播踢出
    TTTRtc_KickedOut_PushRtmpFailed    = 2, // rtmp推流失败
    TTTRtc_KickedOut_ServerOverload    = 3, // 服务器过载
    TTTRtc_KickedOut_MasterExit        = 4, // 主播已退出
    TTTRtc_KickedOut_ReLogin           = 5, // 重复登录
    TTTRtc_KickedOut_NoAudioData       = 6, // 长时间没有上行音频数据
    TTTRtc_KickedOut_NoVideoData       = 7, // 长时间没有上行视频数据
    TTTRtc_KickedOut_NewChairEnter     = 8, // 其他人以主播身份进入
    TTTRtc_KickedOut_ChannelKeyExpired = 9, // Channel Key失效
};

/**
 *  频道模式
 */
typedef NS_ENUM(NSUInteger, TTTRtcChannelProfile) {
    TTTRtc_ChannelProfile_Communication    = 0, // 通信
    TTTRtc_ChannelProfile_LiveBroadcasting = 1, // 直播
    TTTRtc_ChannelProfile_Game_FreeMode    = 2, // 游戏（自由发言模式）
};

/**
 *  用户角色
 */
typedef NS_ENUM(NSUInteger, TTTRtcClientRole) {
    TTTRtc_ClientRole_Anchor      = 1, // 主播
    TTTRtc_ClientRole_Broadcaster = 2, // 副播
    TTTRtc_ClientRole_Audience    = 3, // 观众(默认)
};

/**
 *  音频编码格式
 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioCodecType) {
    TTTRtc_AudioCodec_AAC     = 1, // 码率范围24kbps~96kbps
    TTTRtc_AudioCodec_ISAC_WB = 2, // 码率范围10kbps~32kbps
};

/**
 *  用户离线原因
 */
typedef NS_ENUM(NSUInteger, TTTRtcUserOfflineReason) {
    TTTRtc_UserOffline_Quit           = 1, // 用户主动离开
    TTTRtc_UserOffline_Dropped        = 2, // 因过长时间收不到对方数据包，超时掉线。
    TTTRtc_UserOffline_BecomeAudience = 3, // 当用户身份从主播切换为观众时触发
};

#if TARGET_OS_IOS
/**
*  音频输出路由
*/
typedef NS_ENUM(NSUInteger, TTTRtcAudioOutputRouting)
{
    TTTRtc_AudioOutput_Headset   = 0, // 耳机或蓝牙
    TTTRtc_AudioOutput_Speaker   = 1, // 扬声器
    TTTRtc_AudioOutput_Headphone = 2  // 手机听筒
};

#elif TARGET_OS_OSX

/**
*  音频输出路由
*/
typedef NS_ENUM(NSUInteger, TTTRtcAudioOutputRouting)
{
    TTTRtc_AudioOutput_InternalSpeaker = 0, // 内置扬声器
    TTTRtc_AudioOutput_ExternalSpeaker = 1, // 外置扬声器
    TTTRtc_AudioOutput_Headphones      = 2  // 耳机
};


/**
 *  音频设备类型
 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioDeviceType) {
    TTTRtc_AudioDevice_Input_InternalMicrophone = 1,  // 内置麦克风
    TTTRtc_AudioDevice_Input_ExternalMicrophone = 2,  // 外置麦克风
    TTTRtc_AudioDevice_Output_InternalSpeaker   = 11, // 内置扬声器
    TTTRtc_AudioDevice_Output_ExternalSpeaker   = 12, // 外置扬声器
    TTTRtc_AudioDevice_Output_Headphones        = 13, // 耳机
};
#endif

/**
 *  日志过滤器
 */
typedef NS_ENUM(NSUInteger, TTTRtcLogFilter) {
    TTTRtc_LogFilter_Off      = 0,
    TTTRtc_LogFilter_Debug    = 0x080f,
    TTTRtc_LogFilter_Info     = 0x000f,
    TTTRtc_LogFilter_Warning  = 0x000e,
    TTTRtc_LogFilter_Error    = 0x000c,
    TTTRtc_LogFilter_Critical = 0x0008
};

/**
 *  聊天消息类型
 */
typedef NS_ENUM(NSUInteger, TTTRtcChatType) {
    TTTRtc_ChatType_Text    = 1,
    TTTRtc_ChatType_Picture = 2,
    TTTRtc_ChatType_Audio   = 3,
    TTTRtc_ChatType_Custom  = 4
};

/**
 *  网络质量
 */
typedef NS_ENUM(NSUInteger, TTTNetworkQuality) {
    TTTNetworkQualityExcellent = 1,
    TTTNetworkQualityGood      = 2,
    TTTNetworkQualityCommon    = 3,
    TTTNetworkQualityPoor      = 4,
    TTTNetworkQualityBad       = 5,
    TTTNetworkQualityDown      = 6,
};

/**
 *  网络连接状态
 */
typedef NS_ENUM(NSUInteger, TTTConnectionState) {
    TTTConnectionStateDisconnected = 1, //未加入房间,加入房间失败后，或者离开房间之后
    TTTConnectionStateConnecting = 2,   //加入房间正在建立网络连接
    TTTConnectionStateConnected = 3,    //网络连接建立成功
    TTTConnectionStateReconnecting = 4, //网络连接重连中
    TTTConnectionStateFailed = 5,       //网络连接失败
};

/**
 *  录音音质
 */
typedef NS_ENUM(NSUInteger, TTTAudioRecordQuality) {
    TTTAudioRecordQualityLow = 0,    //10 分钟的文件大小为 2.4M 左右
    TTTAudioRecordQualityMedium = 1, //10 分钟的文件大小为 3.6M 左右
    TTTAudioRecordQualityHigh = 2,   //10 分钟的文件大小为 4.8M 左右
};


