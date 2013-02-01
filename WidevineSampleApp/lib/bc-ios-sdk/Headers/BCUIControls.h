//
//  BCUIControls.h
//  iOS-SDK-Sample-APP
//
//  Created by Keith Peters on 5/3/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "BCComponent.h"
#import <MediaPlayer/MediaPlayer.h>

/**
 * A visual component with standard video playback controls.
 * 
 * ### Allowed to Emit
 * 
 * This component may emit the following events:
 * 
 *  - BCEventHideControls - to respond by hiding the controls
 *  - BCEventShowControls - to respond by showing the controls
 *  - BCEventVideoProgress - to respond by advancing the slider
 *  - BCEventVideoDidPlay - to respond by setting the play/pause button state
 *  - BCEventPaused - to respond by setting the play/pause button state
 *  - BCEventVideoDidEnd - to respond by setting the play/pause button state
 *  - BCEventSetVideo - to respond by resetting the slider and time display
 * 
 * ### Allowed Listeners
 * 
 * This component may listen for the following events:
 * 
 *  - BCEventPlay - to indicate that playback should begin or resume
 *  - BCEventPause - to indicate that playback should halt
 *  - BCEventSeekTo - to indicate where the play head should seek to
 */
@interface BCUIControls : BCComponent
{
    UIView *controlsView;
    MPVolumeView *volumeView;
    UIButton *playPauseButton;
    UIButton *fullScreenButton;
    UISlider *progressBar;
    UILabel *progressLabel;
    UILabel *durationLabel;
}

///---------------------------------------------------------------------------------------
/// @name Creating the Component
///---------------------------------------------------------------------------------------

/**
 * Designated initializer. Initializes the component with the given emitter and view.
 *
 * @param eventEmitter The upstream event emitter through which events will be
 * emitted and listened for.
 * @param viewValue The view into which this component will render itself.
 */
- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter andView:(UIView *)viewValue;

///---------------------------------------------------------------------------------------
/// @name Component Properties
///---------------------------------------------------------------------------------------

/**
 * The UIView containing the controls.
 */
@property (nonatomic, retain) IBOutlet UIView *controlsView;

/**
 * The UIButton that emits play and pause events when clicked.
 */
@property (nonatomic, retain) IBOutlet UIButton *playPauseButton;

/**
 * The MPVolumeView that brings up the AirPlay chooser when clicked.
 */
@property (nonatomic, retain) IBOutlet MPVolumeView *volumeView;

/**
 * The UIButton that emits setFullScreen events when clicked.
 */
@property (nonatomic, retain) IBOutlet UIButton *fullScreenButton;

/**
 * UISlider that tracks the video progress. Also allows scrubbing.
 * Scrubbing emits a seekTo event.
 */
@property (nonatomic, retain) IBOutlet UISlider *progressBar;

/**
 * UILabel that displays formatted time of current video position.
 */
@property (nonatomic, retain) IBOutlet UILabel *progressLabel;
/**
 * UILabel that displays formatted time of duration of video.
 */
@property (nonatomic, retain) IBOutlet UILabel *durationLabel;

/**
 * The duration of the current item.
 */
@property (nonatomic) CMTime duration;

///---------------------------------------------------------------------------------------
/// @name UI Event Handlers
///---------------------------------------------------------------------------------------

/**
 * Called internally when the fullscreen button is clicked.
 * 
 * @param sender The originator of the UI event.
 */
- (IBAction)onFullScreen:(id)sender;

/**
 * Called internally when the play/pause button is clicked. Emits either BCEventPlay
 * or BCEventPause depending on its internal state.
 * 
 * @param sender The originator of the UI event.
 */
- (IBAction)onPlayPause:(id)sender;

/**
 * Called internally when user starts interacting with slider.
 * 
 * @param sender The originator of the UI event.
 */
- (IBAction)onSliderBegin:(id)sender;

/**
 * Called internally when the slider value changes.
 * 
 * @param sender The originator of the UI event.
 */
- (IBAction)onSliderChange:(id)sender;

/**
 * Called internally when the slider is released.
 * 
 * @param sender The originator of the UI event.
 */
- (IBAction)onSliderEnd:(id)sender;

///---------------------------------------------------------------------------------------
/// @name Other Methods
///---------------------------------------------------------------------------------------

/**
 * Formats time in seconds to a readable string in the form of mm:ss.
 * 
 * @param time The time to format.
 * @return Returns the formatted time as a string.
 */
- (NSString *)formatTime:(float)time;

@end
