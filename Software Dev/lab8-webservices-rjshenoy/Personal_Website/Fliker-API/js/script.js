


function APICall() {
  $(document).ready(function() {
    var key = "4554eefd4bb3a6aee341c38ebcd93b40"
    var tags = document.getElementById("tags").value
    var number = document.getElementById("photoGallery").value
    var returnFormat = "json"

    var url ='https://www.flickr.com/services/rest/?method=flickr.photos.search&api_key=' + key 
    + '&tags=' + tags
    + '&tag_mode={tag_mode}&privacy_filter=&safe_search=&content_type=&extras=url_o&per_page='
    + number +'&format='
    + returnFormat +'&nojsoncallback=1'; 
    $.ajax({url:url, dataType:"json"}).then(data => {
      
      var photos = data.photos.photo
      var insert = document.getElementById("photos")
      console.log(photos)
      
      var addRow = true
      var row
      for(var i = 0; i<number; i++){
        
        if(i%3 === 0 || i ===0) {
          addRow=true
          row = document.createElement("div")
          row.setAttribute("class", "row")
        }
        else{
          addRow= false
        }

        var imgInfo = document.createElement("div")
        imgInfo.setAttribute("class", "col-sm-6 col-md-4")
        
        
        var card = document.createElement("div")
        card.setAttribute("class", "card border-primary")
        var cardBody = document.createElement("div")
        cardBody.setAttribute("class", "card-body")

        var cardTitle = document.createElement("p")
        cardTitle.setAttribute("class", "card-title")
        cardTitle.innerHTML=photos[i].title
        var currImg = document.createElement("img")
        currImg.setAttribute("src", photos[i].url_o)
        currImg.setAttribute("width", "300")
        currImg.setAttribute("height", "300")
        
        cardBody.appendChild(cardTitle)
        cardBody.appendChild(currImg)

        card.appendChild(cardBody)
      
        imgInfo.appendChild(card)
        // insert into html doc

        row.appendChild(imgInfo)
        if(addRow){
          insert.appendChild(row)
        }
        
      }

    })
    .catch(error =>{
      console.log(error)
    })
  })
}
