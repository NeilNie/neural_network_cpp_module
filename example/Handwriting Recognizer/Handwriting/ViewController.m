//
//  ViewController.m
//  Handwriting
//
//  Created by Yongyang Nie on 2/3/17.
//  Copyright © 2017 Yongyang Nie. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

-(void)updateImage:(NSImage *)image{
    self.image.image = image;
}

- (IBAction)action:(id)sender {
    self.image.image = self.wt.image;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.wt = [[WritingTrainer alloc] initTrainer];
    NSLog(@"%f", [self.wt evaluate:5000] * 100);
    self.wt.delegate = self;
    //[self.wt getMindWithPath:@"/Users/Neil/Desktop/mindData"];
    [self.wt train:100 epochs:0 correctRate:92.0];
    
    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
