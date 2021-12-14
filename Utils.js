function getRandomValues(count,max) {
    var values = []
    for (var i = 0;i < count;i++) {
        values[i] = Math.floor(Math.random()*max) + 1
        //console.log(values[i])
    }
    console.log(values)
    return values
}
