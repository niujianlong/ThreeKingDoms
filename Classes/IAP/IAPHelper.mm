//
//  IapLayer.m
//
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Recharge.h"

// IAP stuffs.
#import "IAPHelper.h"
#import "NSData+Base64.h"
#import "NSString+SBJSON.h"
#include "SBJSON.h"
#include "UserData.h"
#include "CommonLoading.h"
#include "RechargeManager.h"

#define ProductID_IAP6 "com.sj.300"
#define ProductID_IAP18 "com.sj.1000"
#define ProductID_IAP50 "com.sj.3000"
#define ProductID_IAP128 "com.sj.10000"
#define ProductID_IAP388 "com.sj.35000"
#define ProductID_IAP648 "com.sj.65000"

USING_NS_CC;
USING_NS_CC_EXT;

@implementation IAPHelper

+ (IAPHelper*)sharedInstance
{
    static IAPHelper* sharedInstance = nil;
    if (!sharedInstance)
    {
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            sharedInstance = [[IAPHelper alloc] init];
        });
    }
    
    return sharedInstance;
}

-(id)init
{
    if ((self = [super init])) {
        //---------------------
        //----监听购买结果
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        //申请购买
        /*
         enum{
         IAP0p99=10,
         IAP1p99,
         IAP4p99,
         IAP9p99,
         IAP24p99,
         }buyCoinsTag;
         */
//        [self buy:IAP24p99];
        
        productIds.push_back(ProductID_IAP6);
        productIds.push_back(ProductID_IAP18);
        productIds.push_back(ProductID_IAP50);
        productIds.push_back(ProductID_IAP128);
        productIds.push_back(ProductID_IAP388);
        productIds.push_back(ProductID_IAP648);
        
        string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("AppOrders.plist");
        appOrdersPath = [[NSString alloc]  initWithUTF8String:path.c_str()];
    }
    
    URL = @"https://buy.itunes.apple.com/verifyReceipt";
    
    return self;
}

-(void)buy:(int)type
{
    buyType = type;
    if ([SKPaymentQueue canMakePayments]) {
        //[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
        [self RequestProductData];
        CCLOG("允许程序内付费购买");
    }
    else
    {
        CCLOG("不允许程序内付费购买");
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                            message:@"You can‘t purchase in app store（不允许应用程序内购买）"
                                                           delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
        
        [alerView show];
        [alerView release];
    }
}

-(bool)CanMakePay
{
    return [SKPaymentQueue canMakePayments];
}

-(void)RequestProductData
{
    CCLOG("---------请求对应的产品信息------------");
    NSArray *product = nil;
//    vector<string> productIds = INSTANCE(UserData)->getProductIds();
    
    NSString *productId = [[NSString alloc] initWithUTF8String:productIds[buyType].c_str()];

    product = [[NSArray alloc] initWithObjects:productId,nil];

    NSSet *nsset = [NSSet setWithArray:product];
    SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers: nsset];
    request.delegate = self;
    [request start];
    [product release];
}
//<SKProductsRequestDelegate> 请求协议
//收到的产品信息
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    
    NSLog(@"-----------收到产品反馈信息--------------");
    NSArray *myProduct = response.products;
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
    NSLog(@"产品付费数量: %d", [myProduct count]);
    // populate UI
    for(SKProduct *product in myProduct){
        NSLog(@"product info");
        NSLog(@"SKProduct 描述信息%@", [product description]);
        NSLog(@"产品标题 %@" , product.localizedTitle);
        NSLog(@"产品描述信息: %@" , product.localizedDescription);
        NSLog(@"价格: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
    }
    
    SKPayment *payment = nil;

    payment = [SKPayment paymentWithProduct:myProduct[0]];    //支付$0.99

    CCLOG("---------发送购买请求------------");
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    [request autorelease];
    
}
- (void)requestProUpgradeProductData
{
    CCLOG("------请求升级数据---------");
    NSSet *productIdentifiers = [NSSet setWithObject:@"com.productid"];
    SKProductsRequest* productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];
    
}
//弹出错误信息
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{
    CCLOG("-------弹出错误信息----------");
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:@"网络请求失败，请检查您的网络连接!"
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
    [alerView show];
    [alerView release];
    
    INSTANCE(CommonLoadingFacade)->hideLoading();
}

-(void) requestDidFinish:(SKRequest *)request
{
    NSLog(@"----------反馈信息结束--------------");
}

-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction{
    CCLOG("-----PurchasedTransaction----");
    NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];
    [self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];
    [transactions release];
}

//<SKPaymentTransactionObserver> 千万不要忘记绑定，代码如下：
//----监听购买结果
//[[SKPaymentQueue defaultQueue] addTransactionObserver:self];
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions//交易结果
{
    CCLOG("-----paymentQueue--------");
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased://交易完成
            {
                URL = @"https://buy.itunes.apple.com/verifyReceipt";
                
                BOOL result = YES;
                
                do
                {
                    result = [self putStringToItunes:transaction.transactionReceipt];
                    
                    if (!result) {
                        URL = @"https://sandbox.itunes.apple.com/verifyReceipt";
                        result = [self putStringToItunes:transaction.transactionReceipt];
                    }
                }
                while (!result);
                
                if (result) {
                    //这里给用户添加钱阿，装备阿什么的
                    [self completeTransaction:transaction];
                    INSTANCE(RechargeManager)->rechargeVerification();
                }
                
                CCLOG("-----交易完成 --------");
                CCLOG("不允许程序内付费购买");
//                    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert"
//                                                                        message:@"购买成功啦～娃哈哈"
//                                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
//                    
//                    [alerView show];
//                    [alerView release];
                }
                
                INSTANCE(CommonLoadingFacade)->hideLoading();
                
                break;
            case SKPaymentTransactionStateFailed://交易失败
            {
                [self failedTransaction:transaction];
                CCLOG("-----交易失败 --------");
                UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                                     message:@"购买失败，请重新尝试购买～"
                                                                    delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
                
                [alerView2 show];
                [alerView2 release];
                
                INSTANCE(CommonLoadingFacade)->hideLoading();
            }
                break;
            case SKPaymentTransactionStateRestored://已经购买过该商品
                [self restoreTransaction:transaction];
                CCLOG("-----已经购买过该商品 --------"); 
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表
                CCLOG("-----商品添加进列表 --------");
                break;
            default:
                break;
        }
    }
}
- (void) completeTransaction: (SKPaymentTransaction *)transaction
{
    CCLOG("-----completeTransaction--------");
    // Your application should implement these two methods.
    NSString *product = transaction.payment.productIdentifier;
    if ([product length] > 0) {
        
        NSArray *tt = [product componentsSeparatedByString:@"."];
        NSString *bookid = [tt lastObject];
        if ([bookid length] > 0) {
            [self recordTransaction:bookid];
            [self provideContent:bookid];
        }
    }
    
    NSData* transactionReceipt = transaction.transactionReceipt;
    
    [self recordOrders:transaction.transactionIdentifier receipt:[transactionReceipt base64EncodedString]];
    
    // Remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(NSDictionary *)dictionaryFromPlistData:(NSData *)data
{
    NSError *error;
    NSDictionary *dictionaryParsed = [NSPropertyListSerialization propertyListWithData:data
                                                                               options:NSPropertyListImmutable
                                                                                format:nil
                                                                                 error:&error];
    if (!dictionaryParsed)
    {
        if (error)
        {
            NSLog(@"%@", [error localizedDescription]);
        }
        return nil;
    }
    return dictionaryParsed;
}


-(BOOL)putStringToItunes:(NSData*)iapData{//用户购成功的transactionReceipt
    
    NSString*encodingStr = [iapData base64EncodedString];
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];// autorelease];
    [request setURL:[NSURL URLWithString:URL]];
    [request setHTTPMethod:@"POST"];
    //设置contentType
    [request addValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    //设置Content-Length
    [request setValue:[NSString stringWithFormat:@"%d", [encodingStr length]] forHTTPHeaderField:@"Content-Length"];
    
    NSDictionary* body = [NSDictionary dictionaryWithObjectsAndKeys:encodingStr, @"receipt-data", nil];
    SBJsonWriter *writer = [SBJsonWriter new];
    NSString* requestData = [writer stringWithObject:body];
    CCLog("requestData:%s", [requestData UTF8String]);
    [request setHTTPBody:[requestData dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:YES]];
    NSHTTPURLResponse *urlResponse=nil;
    NSError *errorr=nil;
    NSData *receivedData = [NSURLConnection sendSynchronousRequest:request
                                                 returningResponse:&urlResponse
                                                             error:&errorr];
    
    //解析
    NSString *results=[[NSString alloc]initWithBytes:[receivedData bytes] length:[receivedData length] encoding:NSUTF8StringEncoding];
    CCLOG("-Himi-  %s",[results UTF8String]);
    NSDictionary*dic = [results JSONValue];
    if([[dic objectForKey:@"status"] intValue]==0){//注意，status=@"0" 是验证收据成功
        return true;
    }
    return false;
}

//记录交易
-(void)recordTransaction:(NSString *)product{
    
    
    
    CCLOG("-----记录交易--------");
}

//处理下载内容
-(void)provideContent:(NSString *)product{
    CCLOG("-----下载--------");
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"失败");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
    }
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    
    
}
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction{
    
}

- (void) restoreTransaction: (SKPaymentTransaction *)transaction
{
    [self recordTransaction:transaction.transactionIdentifier];
    [self provideContent: transaction.payment.productIdentifier];
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    
    NSLog(@" 交易恢复处理");
}

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    CCLOG("-------paymentQueue----");
}

-(void)recordOrders:(NSString*)orderId receipt:(NSString*)receipt
{
    storedOrderId = orderId;
    [orders setValue:receipt forKey:orderId];
    [orders writeToFile:appOrdersPath atomically:YES];
}

-(void)removeOrder:(NSString *)orderId
{
    [orders removeObjectForKey:orderId];
    [orders writeToFile:appOrdersPath atomically:YES];
}

-(NSString*)storedOrderId
{
    return storedOrderId;
}

-(void)setStoredOrderId:(NSString*)orderId
{
    storedOrderId = orderId;
}

#pragma mark connection delegate
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    NSLog(@"%@",  [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease]);
}
- (void)connectionDidFinishLoading:(NSURLConnection *)connection{
    
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response{
    switch([(NSHTTPURLResponse *)response statusCode]) {
        case 200:
        case 206:
            break;
        case 304:
            break;
        case 400:
            break;
        case 404:
            break;
        case 416:
            break;
        case 403:
            break;
        case 401:
        case 500:
            break;
        default:
            break;
    }
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    NSLog(@"test");
}

-(void)dealloc
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];//解除监听
    [super dealloc];
}
@end