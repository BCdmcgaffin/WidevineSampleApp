//
//  MPMediaPickerController.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>

@class MPMediaPickerControllerInternal;
@protocol MPMediaPickerControllerDelegate;

// MPMediaPickerController is a UIViewController for visually selecting media items.
// To display it, present it modally on an existing view controller.

MP_EXTERN_CLASS_AVAILABLE(3_0) @interface MPMediaPickerController : UIViewController {
@private
    MPMediaPickerControllerInternal *_internal;
}

- (id)init; // defaults to MPMediaTypeAny
- (id)initWithMediaTypes:(MPMediaType)mediaTypes;
@property (nonatomic, readonly) MPMediaType mediaTypes;

@property (nonatomic, assign) id<MPMediaPickerControllerDelegate> delegate;

@property (nonatomic) BOOL allowsPickingMultipleItems; // default is NO

@property (nonatomic) BOOL showsCloudItems NS_AVAILABLE_IOS(6_0); // default is YES

@property (nonatomic, copy) NSString *prompt; // displays a prompt for the user above the navigation bar buttons

@end

@protocol MPMediaPickerControllerDelegate<NSObject>
@optional

// It is the delegate's responsibility to dismiss the modal view controller on the parent view controller.

- (void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection;
- (void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker;

@end
