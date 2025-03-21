import QtQuick

Canvas {
  id: canvas
  anchors.fill: parent
  z: 1

  // Code to draw a simple arrow on TypeScript canvas got from https://stackoverflow.com/a/64756256/867349
  function arrow(context, fromx, fromy, tox, toy) {
    const dx = tox - fromx;
    const dy = toy - fromy;
    const headlen = Math.sqrt(dx * dx + dy * dy) * 0.3; // length of head in pixels
    const angle = Math.atan2(dy, dx);
    context.beginPath();
    context.moveTo(fromx, fromy);
    context.lineTo(tox, toy);
    context.stroke();
    context.beginPath();
    context.moveTo(tox - headlen * Math.cos(angle - Math.PI / 6), toy - headlen * Math.sin(angle - Math.PI / 6));
    context.lineTo(tox, toy );
    context.lineTo(tox - headlen * Math.cos(angle + Math.PI / 6), toy - headlen * Math.sin(angle + Math.PI / 6));
    context.stroke();
  }

  function drawLine(context,fromx,fromy,tox,toy) {
      context.beginPath();
      context.moveTo(fromx, fromy);
      context.lineTo(tox, toy);
      context.stroke();
  }

  function drawText(context,text,x,y) {
      context.beginPath();
      context.text(text,x,y);
      context.fill();
  }

  function drawArrowLineFromXtoY(fromx,fromy,tox,toy,spacing,barWidth,interval,arrowLength) {
      var ctx = getContext("2d");
      ctx.clearRect(0,0,width,height)
      ctx.strokeStyle="blue"
      drawText(ctx,"交换",fromx,fromy);
      drawArrowLine(fromx,fromy,fromx,fromy + arrowLength) //第一个箭头位置
      drawLine(ctx,fromx,fromy, fromx + interval * (barWidth + spacing),fromy)
      drawArrowLine(fromx + interval * (barWidth + spacing), fromy,fromx + interval * (barWidth + spacing),fromy+arrowLength)  //第二个箭头位置
      requestPaint()
  }

  function drawArrowLine(fromx,fromy,tox,toy) {
      var ctx = getContext("2d");
      // Draw an arrow on given context starting at position (0, 0) -- top left corner up to position (mouseX, mouseY)
      //   determined by mouse coordinates position
      arrow(ctx, fromx, fromy, tox, toy)
  }

  function clear() {
      var ctx = getContext("2d");
      ctx.clearRect(0,0,width,height)
      requestPaint()
  }

  onPaint: {

  }
}
