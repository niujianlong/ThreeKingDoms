//
//  IAPHelper.h
//  IAPTest
#import <UIKit/UIKit.h>

#import <StoreKit/StoreKit.h>

#include <vector>

using std::vector;

enum buyCoinsTag{
    IAP6,
    IAP18,
    IAP50,
    IAP128,
    IAP388,
    IAP648,
};

@interface IAPHelper : NSObject<SKProductsRequestDelegate,SKPaymentTransactionObserver>
{
    int buyType;
    NSString* URL;
    NSMutableDictionary* orders;
    NSString* storedOrderId;
    NSString* appOrdersPath;
    vector<std::string> productIds;
}
+ (IAPHelper*)sharedInstance;
- (void) requestProUpgradeProductData;
-(void)RequestProductData;
-(bool)CanMakePay;
-(void)buy:(int)type;
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction;
- (void) completeTransaction: (SKPaymentTransaction *)transaction;
- (void) failedTransaction: (SKPaymentTransaction *)transaction;
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;
-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;
- (void) restoreTransaction: (SKPaymentTransaction *)transaction;
-(void)provideContent:(NSString *)product;
-(void)recordTransaction:(NSString *)product;
-(BOOL)putStringToItunes:(NSData*)iapData;
-(NSDictionary *)dictionaryFromPlistData:(NSData *)data;
-(void)recordOrders:(NSString*)orderId receipt:(NSString*)receipt;
-(void)removeOrder:(NSString*)orderId;
-(NSString*)storedOrderId;
-(void)setStoredOrderId:(NSString*)orderId;
@end
