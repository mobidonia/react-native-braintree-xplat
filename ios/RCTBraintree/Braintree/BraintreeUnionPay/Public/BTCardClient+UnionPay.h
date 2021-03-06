#pragma message "⚠️ Braintree's UnionPay API for iOS is currently in beta and may change."

#if __has_include("BraintreeCard.h")
#import "BraintreeCard.h"
#else
#import <BraintreeCard/BraintreeCard.h>
#endif

@class BTCardCapabilities, BTCardRequest;

NS_ASSUME_NONNULL_BEGIN

@interface BTCardClient (UnionPay)

/// Fetches the capabilities of a card number.
///
/// This should be used to look up a card PAN to see whether it is UnionPay, and if so, what is required to tokenize it.
///
/// @param cardNumber The card number.
/// @param completion A completion block that is invoked when the card capabilities have been fetched.
- (void)fetchCapabilities:(NSString *)cardNumber
               completion:(void (^)(BTCardCapabilities * _Nullable cardCapabilities, NSError * _Nullable error))completion;

/// Enrolls a UnionPay card and returns an enrollment ID. The `enrollmentID` property of `BTCardRequest` must be set to this ID
/// before the card can be tokenized.
///
/// Attempting to enroll cards that do not require enrollment -- including non-UnionPay cards -- will cause an error. This
/// can be prevented by checking the card's capabilities first.
///
/// @param request A card tokenization request that contains a card, mobile phone number, and country code. Cannot be `nil`.
/// @param completion A callback block that will be invoked on the main thread when enrollment has completed. If enrollment
/// succeeds, `enrollmentID` will contain the enrollment ID and error` will be `nil`; if it fails, `error` will describe the
/// failure and `enrollmentID` will be `nil`.
///
/// @see -fetchCapabilities:completion:
/// @see BTCardClient -tokenizeCard:options:completion:
- (void)enrollCard:(BTCardRequest *)request
        completion:(void (^)(NSString * _Nullable enrollmentID, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
