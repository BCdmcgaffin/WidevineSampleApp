//
//  BCQueueManagementProtocol.h
//  BCiOSSDK
//
//  Created by Jim R. Wilson on 8/22/12.
//
//

#import <Foundation/Foundation.h>

@class BCPlayerItem;
@class BCPlaylist;
@class BCVideo;

/**
 * The BCQueueManagement protocol specifies methods for managing a queue
 * of items.  Its features are inspired by Apple’s AVQueuePlayer behavior.
 *
 * The BCQueueManagement protocol supports basic queue operations such as adding
 * and removing items from the queue, accessing the list of items in the queue
 * and deterimining the current item.
 */
@protocol BCQueueManagementProtocol <NSObject>

///-----------------------------------------------------------------------------
/// @name Player Properties
///-----------------------------------------------------------------------------

/**
 * Returns the items that are currently queued.  The returned array cannot be
 * used to modify the queue.
 *
 * @return NSArray An array of BCPlayerItems that are currently queued.
 */
- (NSArray *)items;

/**
 * Returns the currently cued item.
 *
 * @return BCPlayerItem Item that is currently cued.
 */
- (BCPlayerItem *)currentItem;

///-----------------------------------------------------------------------------
/// @name Controlling Playback
///-----------------------------------------------------------------------------

/**
 * Advances playback to the next item in the queue.  If there are no more videos
 * then calling this method has no effect.
 */
- (void)advanceToNextItem;

/**
 * Advances the queue to the specified item.  If the item is not found then
 * calling this method has no effect.
 *
 * @param item BCPlayerItem Item to be cued.
 */
- (void)advanceToItem:(BCPlayerItem *) item;

/**
 * Set the desired action the player should take when it reaches the end of the
 * playing item.
 *
 * @param actionAtItemEnd Indicates the desired action, value should be one of:
 * - AVPlayerActionAtItemEndAdvance (0) - Advance to the next item if possible.
 * - AVPlayerActionAtItemEndPause (1) - The player should pause.
 * - AVPlayerActionAtItemEndNone (2) - The player should do nothing.
 */
- (void)setActionAtItemEnd:(int)actionAtItemEnd;

///-----------------------------------------------------------------------------
/// @name Adding Items to the Queue
///-----------------------------------------------------------------------------

/**
 * Inserts an BCPlayerItem after the BCPlayerItem that you pass in.
 *
 * @param item BCPlayerItem The item that is being inserted
 * @param afterItem BCPlayerItem The item after which the new item is to be
 * inserted.
 * - If the afterItem is nil then the item will be inserted at the end.
 * - If the afterItem is not found then ***TBD*** - error? insert at end?
 */
- (void)insertItem:(BCPlayerItem *)item afterItem:(BCPlayerItem *)afterItem;

/**
 * Inserts a BCVideo after the BCPlayerItem that you pass in.
 *
 * @param item BCVideo The video that is being inserted
 * @param afterItem BCPlayerItem The item after which the new item is to be
 * inserted.
 * - If the afterItem is nil then the item will be inserted at the end.
 * - If the afterItem is not found then ***TBD*** - error? insert at end?
 * @return BCPlayerItem representation of the BCVideo passed in.
 */
- (BCPlayerItem *)insertVideo:(BCVideo *)videoValue afterItem:(BCPlayerItem *)afterItem;

/**
 * Inserts a BCPlaylist after the BCPlayerItem that you pass in.
 *
 * @param item BCPlaylist The playlist that is being inserted
 * @param afterItem BCPlayerItem The item after which the new item is to be
 * inserted.
 * - If the afterItem is nil then the item will be inserted at the end.
 * - If the afterItem is not found then ***TBD*** - error? insert at end?
 * @return NSArray An array of BCPlayerItems representing the BCPlaylist that
 * was passed in.
 */
- (NSArray *)insertPlaylist:(BCPlaylist *)playlist afterItem:(BCPlayerItem *)afterItem;

///-----------------------------------------------------------------------------
/// @name Removing Items from the Queue
///-----------------------------------------------------------------------------

/**
 * Removes all items from the queue including the currently playing item.
 */
- (void)removeAllItems;

/**
 * Removes the specified item from the queue.  If the item is currently playing
 * then the queue will advance but playback will stop.
 *
 * @param item BCPlayerItem Item to be removed.
 */
- (void)removeItem:(BCPlayerItem *)item;

@end
