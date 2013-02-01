//
//  BCRenditionSet.h
//  BCiOSLibrary
//
//  Created by Jim R. Wilson on 5/29/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BCRendition;

/**
 * A BCRenditionSet is a collection of BCRendition objects which share the same
 * delivery method.
 */
@interface BCRenditionSet : NSObject
{
    NSDictionary *deliveryMethod;
    NSArray *renditions;
}

///---------------------------------------------------------------------------------------
/// @name Creating a Rendition Set
///---------------------------------------------------------------------------------------

/**
 * Designated initializer, takes an array of renditions and a delivery method dictionary.
 * @param renditionsValue Array of BCRendition objects.
 * @param deliveryMethodValue Dictionary of properties describing the delivery method.
 * @return Returns initialized object.
 */
- (id)initWithRenditions:(NSArray *)renditionsValue deliveryMethod:(NSDictionary *)deliveryMethodValue;

/**
 * Factory constructor, takes an array of renditions and a delivery method dictionary.
 * @param renditionsValue Array of BCRendition objects.
 * @param deliveryMethodValue Dictionary of properties describing the delivery method.
 * @return Returns initialized object.
 */
+ (id)renditionSetWithRenditions:(NSArray *)renditionsValue deliveryMethod:(NSDictionary *)deliveryMethodValue;

/**
 * Convenience constructor, takes an array of renditions.
 * @param renditionsValue Array of BCRendition objects.
 * @return Returns initialized object.
 */
- (id)initWithRenditions:(NSArray *)renditionsValue;

/**
 * Convenience factory constructor, takes an array of renditions.
 * @param renditionsValue Array of BCRendition objects.
 * @return Returns initialized object.
 */
+ (id)renditionSetWithRenditions:(NSArray *)renditionsValue;

/**
 * Convenience constructor, takes a single rendition and a delivery method dictionary.
 * @param rendition A single BCRendition object.
 * @param deliveryMethodValue Dictionary of properties describing the delivery method.
 * @return Returns initialized object.
 */
- (id)initWithRendition:(BCRendition *)rendition deliveryMethod:(NSDictionary *)deliveryMethodValue;

/**
 * Convenience factory constructor, takes a single rendition and a delivery method dictionary.
 * @param rendition A single BCRendition object.
 * @param deliveryMethodValue Dictionary of properties describing the delivery method.
 * @return Returns initialized object.
 */
+ (id)renditionSetWithRendition:(BCRendition *)rendition deliveryMethod:(NSDictionary *)deliveryMethodValue;

/**
 * Convenience constructor, takes a single rendition.
 * @param rendition A single BCRendition object.
 * @return Returns initialized object.
 */
- (id)initWithRendition:(BCRendition *)rendition;

/**
 * Convenience factory constructor, takes a single rendition.
 * @param rendition A single BCRendition object.
 * @return Returns initialized object.
 */
+ (id)renditionSetWithRendition:(BCRendition *)rendition;

///---------------------------------------------------------------------------------------
/// @name Video Data
///---------------------------------------------------------------------------------------

/**
 * The delivery method.
 */
@property (nonatomic, readonly) NSDictionary *deliveryMethod;

/**
 * Renditions.
 */
@property (nonatomic, readonly) NSArray *renditions;

@end
