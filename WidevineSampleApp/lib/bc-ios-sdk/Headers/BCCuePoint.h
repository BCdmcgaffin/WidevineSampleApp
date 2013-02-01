//
//  BCCuePoint.h
//  BCiOSLibrary
//
//  Created by Keith Peters on 5/17/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import "BCComponent.h"

/**
 * Represents the data of a single cue point.
 */
@interface BCCuePoint : NSObject
{
    NSString *position;
    NSString *type;
    NSDictionary *properties;
}

///-----------------------------------------------------------------------------
/// @name Creating a Cue Point
///-----------------------------------------------------------------------------

/**
 * Designated initializer, initializes the cue point with a position, type and
 * properties.
 *
 * @param positionValue A string representation of a number or absolute 
 * position.
 * @param typeValue A string indicating which type of cue point this is.
 * @param propertiesValue A dictionary of properties describing this cue point.
 * @return Returns the initialized object.
 */
- (id)initWithPosition:(NSString *)positionValue type:(NSString *)typeValue properties:(NSDictionary *)propertiesValue;

/**
 * Factory initializer, initializes the cue point with a position, type and
 * properties.
 *
 * @param positionValue A string representation of a number or absolute 
 * position.
 * @param typeValue A string indicating which type of cue point this is.
 * @param propertiesValue A dictionary of properties describing this cue point.
 * @return Returns the initialized object.
 */
+ (id)cuePointWithPosition:(NSString *)positionValue type:(NSString *)typeValue properties:(NSDictionary *)propertiesValue;

/**
 * Initializes the cue point with a position and type.
 *
 * @param positionValue A string representation of a number or absolute 
 * position.
 * @param typeValue A string indicating which type of cue point this is.
 * @return Returns the initialized object.
 */
- (id)initWithPosition:(NSString *)positionValue type:(NSString *)typeValue;

/**
 * Convenience factory initializer, initializes the cue point with a position,
 * type and properties.
 *
 * @param positionValue A string representation of a number or absolute position.
 * @param typeValue A string indicating which type of cue point this is.
 * @return Returns the initialized object.
 */
+ (id)cuePointWithPosition:(NSString *)positionValue type:(NSString *)typeValue;

///-----------------------------------------------------------------------------
/// @name Cue Point Data
///-----------------------------------------------------------------------------

/**
 * The position at which this cue point will fire.
 *
 * Possible values:
 *
 *  - "before" - fired immediately before playback begins at the start of a 
 * video. "begin" cue points will fire again if the playhead is reset to the 
 * starting position.
 *  - "after" - fired immediately after a video ends. "after" cue points will 
 * fire again if the end of the video is reached more than once.
 *  - The number of seconds after which the cue point should fire, e.g. @"4.125"
 *
 */
@property (nonatomic, readonly) NSString *position;

/**
 * The type of cue point. This property is intended to allow you to easily 
 * distinguish between different sorts of cue points for the same video but has 
 * no intrinsic meaning. Individual player plugins may set and expect particular 
 * type values. Consult the documentation of the plugins you're using to be sure 
 * your cue point types do not conflict.
 */
@property (nonatomic, readonly) NSString *type;

/**
 * Properties of this cue point. This can be used to associate arbitrary data 
 * with a cue point that is needed for the cue point's handlers to perform their 
 * work. Ad cue points, for example, may include information about the type and 
 * duration of the advertisement to be played.
 */
@property (nonatomic, readonly) NSDictionary *properties;

///-----------------------------------------------------------------------------
/// @name Other Methods
///-----------------------------------------------------------------------------

/**
 * Method for determining whether one cue point comes before or after another.
 * @param otherCuePoint The other cue point to compare to.
 * @return An NSComparisonResult which represents the outcome of comparison.
 */
- (NSComparisonResult)compare:(BCCuePoint *)otherCuePoint;

@end
