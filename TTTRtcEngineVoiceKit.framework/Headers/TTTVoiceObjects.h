//
//  TTTVoiceObjects.h
//  TTTRtcEngineVoiceKit
//
//  Created by yanzhen on 2020/1/3.
//  Copyright © 2020 TTT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TTTVoiceEnumerates.h"

#if TARGET_OS_IOS
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#import <CoreAudio/AudioHardwareBase.h>
#endif

/** 通话相关的统计信息 */
@interface TTTRtcStats : NSObject
/** 通话时长，单位为秒，累计值 */
@property (assign, nonatomic) NSUInteger duration;
/** 发送字节数，累计值 */
@property (assign, nonatomic) NSUInteger txBytes;
/** 接收字节数，累计值 */
@property (assign, nonatomic) NSUInteger rxBytes;
/** 音频发送码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger txAudioKBitrate;
/** 音频接收码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger rxAudioKBitrate;
/** 视频发送码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger txVideoKBitrate;
/** 视频接收码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger rxVideoKBitrate;
/** 房间内的瞬时人数 */
@property (assign, nonatomic) NSUInteger users;

@end

/** 本地音频统计信息 */
@interface TTTRtcLocalAudioStats : NSObject
/** 编码的码率(kbps) */
@property (assign, nonatomic) NSUInteger encodedBitrate;
/** 发送的码率(kbps) */
@property (assign, nonatomic) NSUInteger sentBitrate;
/** 接收的码率(kbps) */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** 音频采集数据长度(Byte) */
@property (assign, nonatomic) NSUInteger captureDataSize;
/** 发送的丢包率 */
@property (assign, nonatomic) CGFloat sentLossRate;
/** rtt */
@property (assign, nonatomic) NSUInteger rtt;

@end

/** 远端音频统计信息 */
@interface TTTRtcRemoteAudioStats : NSObject
/** 用户id */
@property (assign, nonatomic) int64_t uid;
/** 接收码率(kbps) */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** 丢包率 */
@property (assign, nonatomic) CGFloat loseRate;
/** 缓存时长(ms) */
@property (assign, nonatomic) NSUInteger bufferDuration;
/** 延迟(ms) */
@property (assign, nonatomic) NSUInteger delay;
/** 音频编码类型 */
@property (assign, nonatomic) NSUInteger audioCodec;
/** rtt */
@property (assign, nonatomic) NSUInteger rtt;

@end

/** 直播推流配置 */
@interface TTTPublisherConfiguration : NSObject
/** cdn推流地址 */
@property (copy, nonatomic) NSString *publishUrl;
/** 推送纯音频流 默认：YES */
@property (assign, nonatomic) BOOL isPureAudio;
/** cdn音频采样率, 默认48000 可选择8000, 16000, 24000, 32000, 44100, 48000 */
@property (assign, nonatomic) int samplerate;
/** cdn1音频单声道，2双声道 */
@property (assign, nonatomic) int channels;
@property (assign, nonatomic) NSInteger __deprecated bitrate;
@end

/** 直播推流配置生成器 */
@interface TTTPublisherConfigurationBuilder : NSObject

- (TTTPublisherConfigurationBuilder *)setBitrate:(NSInteger)bitrate DEPRECATED_MSG_ATTRIBUTE("");
- (TTTPublisherConfigurationBuilder *)setPublisherUrl:(NSString *)url DEPRECATED_MSG_ATTRIBUTE("use TTTPublisherConfiguration.publishUrl instead");
- (TTTPublisherConfigurationBuilder *)setPublishPureAudio:(BOOL)isPureAudio DEPRECATED_MSG_ATTRIBUTE("use TTTPublisherConfiguration.isPureAudio instead");
- (TTTPublisherConfiguration *)build DEPRECATED_MSG_ATTRIBUTE("");

@end


#if TARGET_OS_OSX
/** 音频设备 */
@interface TTTRtcAudioDevice : NSObject
/** 音频设备ID */
@property (assign, nonatomic) AudioObjectID deviceID;
/** 音频设备类型 */
@property (assign, nonatomic) TTTRtcAudioDeviceType deviceType;
/** 音频设备名称 */
@property (copy, nonatomic) NSString *deviceName;

@end

#endif
