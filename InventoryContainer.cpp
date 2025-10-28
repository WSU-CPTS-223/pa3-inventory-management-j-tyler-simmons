#include "InventoryContainer.hpp"

bool InventoryContainer::loadCSV(const string &filename)
{
    double listPrice = 0.0,
           sellingPrice = 0.0;
    int quantity = 0;
    ifstream infile;
    string line = "",
           uniqId = "",
           productName = "",
           brandName = "",
           asin = "",
           category = "",
           upcEanCode = "",
           listPriceStr = "",
           sellingPriceStr = "",
           quantityStr = "",
           modelNumber = "",
           aboutProduct = "",
           productSpecification = "",
           technicalDetails = "",
           shippingWeights = "",
           productDimensions = "",
           imageStr = "",
           variantsStr = "",
           sku = "",
           productUrl = "",
           stock = "",
           productDetails = "",
           dimensions = "",
           color = "",
           ingredients = "",
           directionsToUse = "",
           isAmazonSeller = "",
           sizeQuantityVariant = "",
           productDescription = "";

    infile.open(filename);

    if (infile.is_open() == false) {
        //throw an error to handle this
        cerr << "Could not open " << filename << endl;

        return false;
    }

    //start parsing here
    if (!getline(infile, line)) {
        return false;
    }

    while (getline(infile, line)) {
        stringstream ss(line);

        uniqId = readCSVField(ss);
        productName = readCSVField(ss);
        brandName = readCSVField(ss);
        asin = readCSVField(ss);
        category = readCSVField(ss);
        upcEanCode = readCSVField(ss);
        listPriceStr = readCSVField(ss);
        sellingPriceStr = readCSVField(ss);
        quantityStr = readCSVField(ss);
        modelNumber = readCSVField(ss);
        aboutProduct = readCSVField(ss);
        productSpecification = readCSVField(ss);
        technicalDetails = readCSVField(ss);
        shippingWeights = readCSVField(ss);
        productDimensions = readCSVField(ss);
        imageStr = readCSVField(ss);
        variantsStr = readCSVField(ss);
        sku = readCSVField(ss);
        productUrl = readCSVField(ss);
        stock = readCSVField(ss);
        productDetails = readCSVField(ss);
        dimensions = readCSVField(ss);
        color = readCSVField(ss);
        ingredients = readCSVField(ss);
        directionsToUse = readCSVField(ss);
        isAmazonSeller = readCSVField(ss);
        sizeQuantityVariant = readCSVField(ss);
        productDescription = readCSVField(ss);

        //convert certain fields to numeric values
        listPrice = 0.0;
         if (listPriceStr != "NA") {
            if (!listPriceStr.empty() && listPriceStr[0] == '$') {
                listPriceStr = listPriceStr.substr(1);
            }
            listPrice = stod(listPriceStr);
        }

        sellingPrice = 0.0;
        if (sellingPriceStr != "NA") {
            if (!sellingPriceStr.empty() && sellingPriceStr[0] == '$') {
                sellingPriceStr = sellingPriceStr.substr(1);
            }
            sellingPrice = stod(sellingPriceStr);
        }

        quantity = 0;
        if (quantityStr != "NA") {
            quantity = stoi(quantityStr);
        }

        //handling string vectors
        vector<string> imageUrls;
        if (imageStr != "NA") {
            stringstream imgSS(imageStr);
            string img;
            while (getline(imgSS, img, '|')) {
                imageUrls.push_back(img);
            }
        }

        vector<string> variants;
        if (variantsStr != "NA") {
            stringstream varSS(variantsStr);
            string var;
            while (getline(varSS, var, '|')) {
                variants.push_back(var);
            }
        }

        Product newProduct(
            uniqId, productName, brandName, asin, category, upcEanCode,
            listPrice, sellingPrice, quantity, modelNumber, aboutProduct,
            productSpecification, technicalDetails, shippingWeights, productDimensions,
            imageUrls, variants, sku, productUrl, stock, productDetails,
            dimensions, color, ingredients, directionsToUse, isAmazonSeller,
            sizeQuantityVariant, productDescription
        );

        mProductsById.insert(uniqId, newProduct);         //Products mapped by uniqID
        
        vector<Product>* categoryProducts = this->mProductsByCategory.find(category);

        if (categoryProducts != nullptr) {
            categoryProducts->push_back(newProduct);
        }
        else {
            this->mProductsByCategory.insert(category, vector<Product>{newProduct});
        }
    }

    infile.close();

    return true;
}

Product *InventoryContainer::getProductById(const string &uniqId)
{
    return this->mProductsById.find(uniqId);
}

vector<Product> InventoryContainer::getProductsByCategory(const string &category)
{
    vector<Product> searchResults;
    vector<Product>* categoryProducts = this->mProductsByCategory.find(category);

    if (categoryProducts != nullptr) {
        searchResults = *categoryProducts;
    }

    return searchResults;
}

string InventoryContainer::readCSVField(stringstream &ss)
{
    string token;
    char scopeOut = '\0';
    bool insideQuotes = false;

    if (ss.peek() == '"') {
        ss.get(scopeOut); //consumes opening quote
        insideQuotes = true;

        while (insideQuotes && ss.get(scopeOut)) {
            if (scopeOut == '"') {
                if (ss.peek() == '"') {
                    token += scopeOut;
                    ss.get(scopeOut);   //consumes final quote
                }
                else {
                    insideQuotes = false;   //closing quote has been found
                }
            }
            else {
                token += scopeOut;
            }
        }

        //skip the comma at the end of the field if there is one
        if (ss.peek() == ',') {
            ss.get(scopeOut);
        }
    }
    else {
        getline(ss, token, ',');    //for a normal field with no quotes
    }
    //for empty fields
    if (token.empty()) {
        token = "NA";
    }

    return token;
}