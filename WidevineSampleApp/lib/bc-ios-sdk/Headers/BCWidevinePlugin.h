//
//  BCWidevinePlugin.h
//  WidevinePlugin
//
//  Created by David McGaffin on 1/17/13.
//
//

#import <Foundation/Foundation.h>
#import "BCComponent.h"
#import "BCQueuePlayer.h"
#import "BCCatalog.h"
#import "BCPlaylist.h"


#define widevineStatus @"widevineStatus"
#define widevineAction @"widevineAction"

#define BCEventWidevine @"BCEventWidevine"

@interface BCWidevinePlugin : BCComponent

/**
 * Initialize the BCWidevinePlugin. A media api token with URL access is required 
 * to initialize the BCCatalog object for future BC Media API calls.
 */
- (id)initWithToken:(NSString *)token;

/**
 * Initialize the BCWidevinePlugin. A media api token with URL access is required 
 * to initialize the BCCatalog object for future BC Media API calls.
 */
- (id)initWithToken:(NSString *)token baseURL:(NSString *)baseURL;

/**
 * Add a BCVideo object to the playback queue.
 */
- (void)queueVideo:(BCVideo *)video;

/**
 * Initialization state of Widevine access.
 */
@property (nonatomic,readonly) BOOL widevineInitialized;

/**
 * if true, playback of a video will begin as soon as it becomes the active video
 * in the queue.
 */
@property (nonatomic) BOOL autoPlay;

/**
 * BCCatalog reference
 */
@property (nonatomic,readonly,retain) BCCatalog *catalog;

/**
 * Media API Read Token with URL access.
 */
@property (nonatomic,readonly,retain) NSString *apiToken;

/**
 * iOS SDK player
 */
@property (nonatomic,readonly,retain) BCQueuePlayer *player;

/**
 * List of videos to play, stored as BCVideo objects.
 */
@property (nonatomic,retain) BCPlaylist *playlist;

/**
 * Video info for the video currently playing.
 */
@property (nonatomic,readonly,retain) NSDictionary *videoInfo;

/**
 * Audio info for the video currently playing.
 */
@property (nonatomic,readonly,retain) NSDictionary *audioInfo;

/**
 * Information for the license policy in effect for the current video.
 */
@property (nonatomic,readonly,retain) NSDictionary *licensePolicy;

/**
 * Bitrates available for the current video.
 */
@property (nonatomic,readonly,retain) NSArray *bitrates;

/**
 * Current playback bitrate.
 */
@property (nonatomic,readonly,retain) NSNumber *currentBitrate;

/**
 * Stops playback of video.
 */
- (void)stop;

/**
 * Sets user data for Widevine request.
 */
- (void)setWidevineUserData:(NSString *)userData;

/**
 * Releases Widevine resources.
 */
- (void)unload;

/**
 * Find a playlist by its ID.
 * When the playlist is returned by BCCatalog, the playback queue will be populated with the playlist items.
 */
- (void)findPlaylistByID:(NSString *)playlistID options:(NSDictionary *)options callBlock:(BCPlaylistResponseBlock)responseBlock;

/**
 * Find a playlist by its reference ID.
 * When the playlist is returned by BCCatalog, the playback queue will be populated with the playlist items.
 */
- (void)findPlaylistByReferenceID:(NSString *)referenceID options:(NSDictionary *)options callBlock:(BCPlaylistResponseBlock)responseBlock;

/** 
 * Find a video by its ID.
 * When the video is returned by BCCatalog, it will be appended to the playback queue.
 */
- (void)findVideoByID:(NSString *)videoID options:(NSDictionary *)options callBlock:(BCVideoResponseBlock)responseBlock;

/**
 * Find a video by its reference ID.
 * When the video is returned by BCCatalog, it will be appended to the playback queue.
 */
- (void)findVideoByReferenceID:(NSString *)referenceID options:(NSDictionary *)options callBlock:(BCVideoResponseBlock)responseBlock;


@end
