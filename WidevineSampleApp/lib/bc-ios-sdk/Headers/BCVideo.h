//
//  BCVideoObject.h
//  BCiOSLibrary
//
//  Created by Keith Peters on 5/17/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BCRendition;
@class BCRenditionSet;

/**
 * Represents the information required to play a video.
 */
@interface BCVideo : NSObject
{
    NSDictionary *properties;
    NSArray *renditionSets;
}

///---------------------------------------------------------------------------------------
/// @name Creating a Video
///---------------------------------------------------------------------------------------

/**
 * Designated initializer, takes an array rendition sets and dictionary of properties.
 * @param renditionSetsValue Array of BCRenditionSet objects.
 * @param propertiesValue Dictionary of properties which describe this video.
 * @return Returns initialized object.
 */
- (id)initWithRenditionSets:(NSArray *)renditionSetsValue properties:(NSDictionary *)propertiesValue;

/**
 * Factory initializer, takes an array of rendition sets and a dictionary of properties.
 * @param renditionSetsValue Array of BCRenditionSet objects.
 * @param propertiesValue Dictionary of properties which describe this video.
 * @return Returns initialized object.
 */
+ (id)videoWithRenditionSets:(NSArray *)renditionSetsValue properties:(NSDictionary *)propertiesValue;

/**
 * Convenience initializer, takes a single rendition set and dictionary of properties.
 * @param renditionSet A single BCRenditionSet.
 * @param propertiesValue Dictionary of properties which describe this video.
 * @return Returns initialized object.
 */
- (id)initWithRenditionSet:(BCRenditionSet *)renditionSet properties:(NSDictionary *)propertiesValue;

/**
 * Factory initializer, takes an array of rendition sets and a dictionary of properties.
 * @param renditionSet A single BCRenditionSet.
 * @param propertiesValue Dictionary of properties which describe this video.
 * @return Returns initialized object.
 */
+ (id)videoWithRenditionSet:(BCRenditionSet *)renditionSet properties:(NSDictionary *)propertiesValue;

/**
 * Convenience initializer, takes a single rendition and a dictionary of properties.
 * @param rendition A single BCRendition object.
 * @param propertiesValue Dictionary of properties which describe this video.
 * @return Returns initialized object.
 */
- (id)initWithRendition:(BCRendition *)rendition properties:(NSDictionary *)propertiesValue;

/**
 * Factory initializer, takes a single rendition and dictionary of properties.
 * @param rendition A single BCRendition object.
 * @param propertiesValue Dictionary of properties which describe this video.
 * @return Returns initialized object.
 */
+ (id)videoWithRendition:(BCRendition *)rendition properties:(NSDictionary *)propertiesValue;

/**
 * Factory initializer, takes a URL
 * @param url A single NSURL source for the video.
 * @param propertiesValue Dictionary of properties which describe this video.
 * @return Returns initialized object.
 */
+ (id)videoWithURL:(NSURL *)url properties:(NSDictionary *)propertiesValue;

///---------------------------------------------------------------------------------------
/// @name Cue Points
///---------------------------------------------------------------------------------------

/**
 * Returns a new video with the specified cue points.
 * @param cuePoints A NSArray of BCCuePoints to set.
 * @return a BCVideo with cue points
 */
- (BCVideo *)withCuePoints:(NSArray *)cuePointsValue;

/**
 * The cue points associated with this video.
 */
@property (nonatomic, readonly) NSArray *cuePoints;

///---------------------------------------------------------------------------------------
/// @name Video Data
///---------------------------------------------------------------------------------------

/**
 * Properties of this video (ex: name, description).
 */
@property (nonatomic, readonly) NSDictionary *properties;

/**
 * An array of rendition sets. Each rendition set contains one or more renditions.
 */
@property (nonatomic, readonly) NSArray *renditionSets;

@end
