//
//  BCRendition.h
//  BCiOSLibrary
//
//  Created by Keith Peters on 5/22/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Represents a single rendition of a video.
 */
@interface BCRendition : NSObject
{
    NSDictionary *properties;
}

///---------------------------------------------------------------------------------------
/// @name Creating a Rendition
///---------------------------------------------------------------------------------------

/**
 * Designated initializer, creates a rendition with the supplied properties.
 * @param propertiesValue Dictionary of properties describing this rendition.
 * @return Returns the initialized rendition object.
 */
- (id)initWithProperties:(NSDictionary *)propertiesValue;

/**
 * Factory initializer, creates a rendition with the supplied properties.
 * @param propertiesValue Dictionary of properties describing this rendition.
 * @return Returns the initialized rendition object.
 */
+ (id)renditionWithProperties:(NSDictionary *)propertiesValue;

/**
 * Convenience initializer, common to create a rendition with a URL.
 * @param url URL pointing to the rendition content.
 * @return Returns the initialized rendition object.
 */
- (id)initWithURL:(NSURL *)url;

/**
 * Convenience factory initializer, common to create a rendition with a URL.
 * @param url URL pointing to the rendition content.
 * @return Returns the initialized rendition object.
 */
+ (id)renditionWithURL:(NSURL *)url;

///---------------------------------------------------------------------------------------
/// @name Rendition Data
///---------------------------------------------------------------------------------------

/**
 * The URL to access the video.
 */
@property (nonatomic, readonly) NSDictionary *properties;

@end
