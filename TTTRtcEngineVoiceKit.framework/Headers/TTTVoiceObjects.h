//
//  TTTVoiceObjects.h
//  TTTRtcEngineVoiceKit
//
//  Created by yanzhen on 2020/1/3.
//  Copyright © 2020 TTT. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IOS
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#endif

/**
 *  通话相关的统计信息
 */
@interface TTTRtcStats : NSObject

@property (assign, nonatomic) NSUInteger duration;        // 通话时长，单位为秒，累计值
@property (assign, nonatomic) NSUInteger txBytes;         // 发送字节数，累计值
@property (assign, nonatomic) NSUInteger rxBytes;         // 接收字节数，累计值
@property (assign, nonatomic) NSUInteger txAudioKBitrate; // 音频发送码率 (kbps)，瞬时值
@property (assign, nonatomic) NSUInteger rxAudioKBitrate; // 音频接收码率 (kbps)，瞬时值
@property (assign, nonatomic) NSUInteger users;           // 房间内的瞬时人数

@end

/**
 *  本地音频统计信息
 */
@interface TTTRtcLocalAudioStats : NSObject

@property (assign, nonatomic) NSUInteger encodedBitrate;  // 编码的码率(kbps)
@property (assign, nonatomic) NSUInteger sentBitrate;     // 发送的码率(kbps)
@property (assign, nonatomic) NSUInteger receivedBitrate; // 接收的码率(kbps)
@property (assign, nonatomic) NSUInteger captureDataSize; // push数据量
@property (assign, nonatomic) CGFloat sentLossRate;       // 发送的丢包率
@property (assign, nonatomic) NSUInteger rtt;

@end

/**
 *  远端音频统计信息
 */
@interface TTTRtcRemoteAudioStats : NSObject

@property (assign, nonatomic) int64_t uid;
@property (assign, nonatomic) NSUInteger receivedBitrate;   // 接收码率
@property (assign, nonatomic) CGFloat loseRate;             // 丢包率
@property (assign, nonatomic) NSUInteger bufferDuration;    // 缓存时长
@property (assign, nonatomic) NSUInteger delay;             // 延迟
@property (assign, nonatomic) NSUInteger audioCodec;
@property (assign, nonatomic) NSUInteger rtt;

@end

/**
 *  直播推流配置
 */
@interface TTTPublisherConfiguration : NSObject

@property (assign, nonatomic) NSInteger bitrate;       // 旁路直播输出码流的码率。默认设置为 500 Kbps
@property (copy, nonatomic) NSString *publishUrl;      // 合图推流地址
@property (assign, nonatomic) BOOL isPureAudio;        // 推送纯音频流

@end

/**
 *  直播推流配置生成器
 */
@interface TTTPublisherConfigurationBuilder : NSObject

- (TTTPublisherConfigurationBuilder *)setBitrate:(NSInteger)bitrate;
- (TTTPublisherConfigurationBuilder *)setPublisherUrl:(NSString *)url;
- (TTTPublisherConfigurationBuilder *)setPublishPureAudio:(BOOL)isPureAudio;
- (TTTPublisherConfiguration *)build;

@end


#if TARGET_OS_OSX
/**
 *  音频设备
 */
@interface TTTRtcAudioDevice : NSObject

@property (assign, nonatomic) AudioDeviceID deviceID;           // 音频设备ID
@property (assign, nonatomic) TTTRtcAudioDeviceType deviceType; // 音频设备类型
@property (copy, nonatomic) NSString *deviceName;               // 音频设备名称

@end

#endif
