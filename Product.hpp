#include <iostream>
#include <vector>
using namespace std;

//Container class for all the .csv info
class Product {
    public:
        //constructor
        Product(string uniqId = string(), string productName = string(),
            string brandName = string(), string asin = string (), string category = string(),
            string upcEanCode = string(), double listPrice = 0.0, double sellingPrice = 0.0,
            int quantity = 0, string modelNumber = string(), string aboutProduct = string(),
            string productSpecification = string(), string technicalDetails = string(),
            string shippingWeight = string(), string productDimensions = string(), 
            vector<string> imageUrls = vector<string>(), vector<string> variants = vector<string>(),
            string sku = string(), string productUrl = string(), string stock = string(),
            string productDetails = string(), string dimensions = string(), string color = string(),
            string ingredients = string(), string directionsToUse = string(), string isAmazonSeller = string(),
            string sizeQuantityVariant = string(), string productDescription = string())
                : mUniqId(uniqId), mProductName(productName), mBrandName(brandName), mAsin(asin),
                mCategory(category), mUpcEanCode(upcEanCode), mListPrice(listPrice), mSellingPrice(sellingPrice),
                mQuantity(quantity), mModelNumber(modelNumber), mAboutProduct(aboutProduct),
                mProductSpecification(productSpecification), mTechnicalDetails(technicalDetails),
                mShippingWeight(shippingWeight), mProductDimensions(productDimensions), mImageUrls(imageUrls),
                mVariants(variants), mSku(sku), mProductUrl(productUrl), mStock(stock),
                mProductDetails(productDetails), mDimensions(dimensions), mColor(color), mIngredients(ingredients),
                mDirectionsToUse(directionsToUse), mIsAmazonSeller(isAmazonSeller), mSizeQuantityVariant(sizeQuantityVariant),
                mProductDescription(productDescription) {}

        //destructor;
        ~Product() = default;

        //debug helper
        void printSummary() const {
        cout << mUniqId << " | " << mProductName
             << " | " << mCategory
             << " | $" << mSellingPrice << endl;
         }

        //data members
        string mUniqId;
        string mProductName;
        string mBrandName;
        string mAsin;
        string mCategory;
        string mUpcEanCode;
        double mListPrice;
        double mSellingPrice;
        int mQuantity;
        string mModelNumber;
        string mAboutProduct;
        string mProductSpecification;
        string mTechnicalDetails;
        string mShippingWeight;
        string mProductDimensions;
        vector<string> mImageUrls;
        vector<string> mVariants;
        string mSku;
        string mProductUrl;
        string mStock;
        string mProductDetails;
        string mDimensions;
        string mColor;
        string mIngredients;
        string mDirectionsToUse;
        string mIsAmazonSeller;
        string mSizeQuantityVariant;
        string mProductDescription;

    private:
        //empty for now
};