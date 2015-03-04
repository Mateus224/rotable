var ToPay = 0;


function setPrices(SetToPay)
{
    ToPay=SetToPay
    console.log(ToPay)
    getPrices()

}

function getPrices ()
{

    priceLabel.text ="To Pay: "+ToPay.toFixed(2)+"€"
}
