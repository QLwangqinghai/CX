//
//  ViewController.m
//  Demo
//
//  Created by clf on 2020/5/11.
//  Copyright © 2020 clf. All rights reserved.
//

#import "ViewController.h"




static const UInt8 __XUtf8CharByteCountTable[32] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4,
};

/*
 EF BB BF
 
    0000 0000~0000 007F 0xxxxxxx
 　　0000 0080~0000 07FF 110xxxxx 10xxxxxx
 　　0000 0800~0000 FFFF 1110xxxx 10xxxxxx 10xxxxxx
 　　0001 0000~001F FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 
 
 
 
 
 
 　　0020 0000~03FF FFFF 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 　　0400 0000~7FFF FFFF 1111110x 10xxxxxx ... 10xxxxxx
 */

BOOL IsTextUTF8(uint8_t * bytes, size_t length) {
    size_t begin = 0;
    size_t end = length;
    size_t offset = 0;
    if (length >= 3) {
        //check bom
        if (0xEF == bytes[0] && 0xBB == bytes[1] && 0xBF == bytes[2]) {
            begin = 3;
            offset = 3;
        }
    }
    size_t errorIndex = SIZE_T_MAX;
    while (length - offset > 0 && SIZE_T_MAX == errorIndex) {
        uint8_t byte = bytes[offset];
        if (byte == 0x0) {
            //终止符
            end = offset;
            break;
        } else if (byte < 0x80) {
            //1
            offset += 1;
        } else if ((byte & 0xE0) == 0xC0) {
            //2
            if (offset > length-2) {
                errorIndex = offset;
                break;
            }
            if ((byte & 0x1F) == 0) {
                errorIndex = offset;
                break;
            }
            uint8_t tmp = bytes[offset+1];
            if (byte == 0xC0 && tmp == 0x80) {
                end = offset;
                break;
            }
            if (tmp >= 0x80 && tmp <= 0xBF) {
                offset += 2;
            } else {
                errorIndex = offset;
            }
        } else if ((byte & 0xF0) == 0xE0) {
            //3
            if (offset > length-3) {
                errorIndex = offset;
                break;
            }
            if ((byte & 0xF) == 0) {
                errorIndex = offset;
                break;
            }
            uint16_t tmp = *(uint16_t *)(bytes + offset + 1);
            if (byte == 0xE0 && tmp == 0x8080) {
                end = offset;
                break;
            }
            if ((tmp & 0xC0C0) == 0x8080) {
                offset += 3;
            } else {
                errorIndex = offset;
                break;
            }
        } else if ((byte & 0xF8) == 0xF0) {
            //4
            if (offset > length-4) {
                errorIndex = offset;
                break;
            }
            if ((byte & 0x7) == 0) {
                errorIndex = offset;
                break;
            }
            uint32_t tmp = *(uint32_t *)(bytes + offset);
            
            //大端
            if ((tmp & 0xF8C0C0C0) == 0xF0808080) {
                if (tmp == 0xF0808080) {
                    end = offset;
                    break;
                }
                offset += 4;
            } else {
                errorIndex = offset;
                break;
            }
            
            
            //小端
            if ((tmp & 0xC0C0C0F8) == 0x808080F0) {
                if (tmp == 0x808080F0) {
                    end = offset;
                    break;
                }
                offset += 4;
            } else {
                errorIndex = offset;
                break;
            }
        }
    }

    return true;
}
//
//    uint8_t * str = bytes;
//
//
//
//
//
//
//
//
//
//
//
//
//    DWORD nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节
//    UCHAR chr;
//    BOOL bAllAscii=TRUE; //如果全部都是ASCII, 说明不是UTF-8
//    for(int i=0; i<length; ++i)
//    {
//        chr= *(str+i);
//        if( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
//            bAllAscii= FALSE;
//        if(nBytes==0) //如果不是ASCII码,应该是多字节符,计算字节数
//        {
//            if(chr>=0x80)
//            {
//                if(chr>=0xFC&&chr<=0xFD)
//                    nBytes=6;
//                else if(chr>=0xF8)
//                    nBytes=5;
//                else if(chr>=0xF0)
//                    nBytes=4;
//                else if(chr>=0xE0)
//                    nBytes=3;
//                else if(chr>=0xC0)
//                    nBytes=2;
//                else
//                    return FALSE;
//
//                nBytes--;
//            }
//        }
//        else //多字节符的非首字节,应为 10xxxxxx
//        {
//            if( (chr&0xC0) != 0x80 )
//                return FALSE;
//
//            nBytes--;
//        }
//    }
//    if( nBytes > 0 ) //违返规则
//        return FALSE;
//    if( bAllAscii ) //如果全部都是ASCII, 说明不是UTF-8
//        return FALSE;
//
//    return TRUE;
//}







@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    
    for (UInt i=0; i<32; i++) {
        if (i < 0x10) {
            printf("1, ");
        } else if ((i & 0x1C) == 0x18) {
            printf("2, ");
        } else if ((i & 0x1E) == 0x1C) {
            printf("3, ");
        } else if ((i & 0x1F) == 0x1E) {
            printf("4, ");
        }
    }
    printf("\n");
    
    

    for (UInt byte=0; byte<256; byte++) {
        if (byte < 0x80) {


        } else if ((byte & 0xE0) == 0xC0) {
            printf("2, ");
        } else if ((byte & 0xF0) == 0xE0) {
            printf("3, ");
        } else if ((byte & 0xF8) == 0xF0) {
            printf("4, ");
        }
        
        
    }
    printf("\n");

    uint8_t bytes[] = {0xF1, 0x80, 0x80, 0xA1, 0};
    
    NSString * str = [[NSString alloc] initWithBytes:bytes length:4 encoding:NSUTF8StringEncoding];
    NSLog(@"%@", str);
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
