//
//  ViewController.h
//  libNeuralNets Demo
//
//  Created by Yongyang Nie on 9/3/2017.
//  Modified and improve upon in 2022.
//  Copyright (c) 2022 Yongyang Nie. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "libNeuralNets/src/LibNeuralNets.h"
#import "libNeuralNets/include/libNeuralNets/module/Module.h"

@interface ViewController : UIViewController <UIActionSheetDelegate> {
    
    CGPoint lastPoint;
    CGFloat red;
    CGFloat green;
    CGFloat blue;
    CGFloat brush;
    CGFloat opacity;
    BOOL mouseSwiped;
    NSTimer *timer;
    int time;
}

@property Module *module;
@property (weak, nonatomic) IBOutlet UIImageView *mainImage;
@property (weak, nonatomic) IBOutlet UIImageView *tempDrawImage;
@property (weak, nonatomic) IBOutlet UILabel *result;
@property (weak, nonatomic) IBOutlet UILabel *percentage;
@property (weak, nonatomic) IBOutlet UIView *rec;
@property (weak, nonatomic) IBOutlet UIImageView *processedImage;
@property CGRect boundingBox;

- (IBAction)reset:(id)sender;

@end
