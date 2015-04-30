//
//  ViewController.h
//  btle_test
//
//  Created by Erkki  on 03/04/15.
//  Copyright (c) 2015 Erkki Silvola. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "btle/central/collectorsimpleobjc.h"

@interface ViewController : UIViewController<collectorsimpleobjc_delegate>

@property (nonatomic) collectorsimpleobjc* simple_;

@end

