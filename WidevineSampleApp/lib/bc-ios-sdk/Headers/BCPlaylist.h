//
//  BCPlaylist.h
//  BCiOSLibrary
//
//  Created by Keith Peters on 5/22/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BCVideo;

/**
 * Represents a playlist of videos.
 */
@interface BCPlaylist : NSObject
{
    NSArray *videos;
    NSDictionary *properties;
}

///---------------------------------------------------------------------------------------
/// @name Creating a Playlist
///---------------------------------------------------------------------------------------

/**
 * Designated initializer, creates a playlist with the specified videos and properties.
 * @param videosValue Array of BCVideo objects.
 * @param propertiesValue Dictionary of properties for this playlist.
 * @return Returns the initialized object.
 */
- (id)initWithVideos:(NSArray *)videosValue properties:(NSDictionary *)propertiesValue;

/**
 * Factory initializer, creates a playlist with the specified videos and properties.
 * @param videosValue Array of BCVideo objects.
 * @param propertiesValue Dictionary of properties for this playlist.
 * @return Returns the initialized object.
 */
+ (id)playlistWithVideos:(NSArray *)videosValue properties:(NSDictionary *)propertiesValue;

/**
 * Convenience initializer, creates a playlist with the specified videos.
 * @param videosValue Array of BCVideo objects.
 * @return Returns the initialized object.
 */
- (id)initWithVideos:(NSArray *)videosValue;

/**
 * Convenience factory initializer, creates a playlist with the specified videos.
 * @param videosValue Array of BCVideo objects.
 * @return Returns the initialized object.
 */
+ (id)playlistWithVideos:(NSArray *)videosValue;

/**
 * Convenience initializer, creates a playlist with the specified video and properties.
 * @param video A single BCVideo object.
 * @param propertiesValue Dictionary of properties for this playlist.
 * @return Returns the initialized object.
 */
- (id)initWithVideo:(BCVideo *)video properties:(NSDictionary *)propertiesValue;

/**
 * Convenience factory initializer, creates a playlist with the specified video and properties.
 * @param video A single BCVideo object.
 * @param propertiesValue Dictionary of properties for this playlist.
 * @return Returns the initialized object.
 */
+ (id)playlistWithVideo:(BCVideo *)video properties:(NSDictionary *)propertiesValue;

/**
 * Convenience initializer, creates a playlist with the specified video.
 * @param video A single BCVideo object.
 * @return Returns the initialized object.
 */
- (id)initWithVideo:(BCVideo *)video;

/**
 * Convenience factory initializer, creates a playlist with the specified video.
 * @param video A single BCVideo object.
 * @return Returns the initialized object.
 */
+ (id)playlistWithVideo:(BCVideo *)video;

///---------------------------------------------------------------------------------------
/// @name Playlist Data
///---------------------------------------------------------------------------------------

/**
 * An array of videos in the playlist.
 */
@property (nonatomic, readonly) NSArray *videos;

/**
 * A dictionary of properties about playlist.
 */
@property (nonatomic, readonly) NSDictionary *properties;

///---------------------------------------------------------------------------------------
/// @name Other Methods
///---------------------------------------------------------------------------------------

/**
 * Convenience accessor for the number of videos in this playlist.
 * @return Returns the number of videos in the playlist.
 */
- (int)count;

@end
