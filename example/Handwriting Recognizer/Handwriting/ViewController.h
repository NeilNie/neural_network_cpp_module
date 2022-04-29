//
//  ViewController.h
//  Handwriting
//
//  Created by Yongyang Nie on 2/3/17.
//  Copyright © 2017 Yongyang Nie. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "WritingTrainer.h"
#import <Foundation/Foundation.h>
#import <malloc/malloc.h>

@interface ViewController : NSViewController <WritingTrainerDelegate>

@property (nonatomic, strong) WritingTrainer *wt;
@property (weak) IBOutlet NSImageView *image;

@end

