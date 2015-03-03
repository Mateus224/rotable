var ToPay = 0;


function setPrices(SetToPay)
{
    ToPay=SetToPay
    getPrices()

}

function getPrices ()
{

    priceLabel.text ="To Pay: "+ToPay.toFixed(2)+"€"
    //return ToPay
}
