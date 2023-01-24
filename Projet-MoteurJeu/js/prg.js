let cnv = document.getElementById("myCanvas");
let ctx = cnv.getContext("2d");

let map_cnv = document.createElement('canvas');
let tilemap;
let tilemap_loaded = 0;
let tileset;
let tileset_loaded = 0;
let tileset_elts = [];
let layer;
let cam_x = 0;
let cam_y = 0;
let ballSize = 10;
let posX = 350;
let posY = 250;

ctx.imageSmoothingEnabled= false;
let all_img = [];
let img = new Image();
let anim_id = -1;
let X = 0;
let Y = 150;
let nbmax = 0;
let nbr = 100;
let Horde = [[X, Y]];


img.src = "./tilesets/Neo Geo NGCD - Metal Slug 3 - Rebel Biker.png";
img.onload = function() {
  let canvas1 = document.createElement('canvas');
  canvas1.width = 37*5;
  canvas1.height = 45*4;
  let context1 = canvas1.getContext('2d');
  context1.drawImage(img, 0,0,37*5,45*4);
  for(let j = 0; j < 4; j += 1) {
    let imax = 5;
    if(j == 3) { imax = 3; }
    for(let i = 0; i < imax; i += 1) {
      let canvasImageData1 = context1.getImageData(i*37, j*45, 37, 45);
      let canvas2 = document.createElement('canvas');
      canvas2.width = 37;
      canvas2.height = 45;
      let context2 = canvas2.getContext('2d');
      context2.putImageData(canvasImageData1, 0,0);
      all_img.push(canvas2);
    }
  }
  anim_id = 0;
};

function getRandomIntInclusive(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min +1)) + min;
}

var randx1 = getRandomIntInclusive(-100, 50);
var randy1 = getRandomIntInclusive(30, 100);

var randx2 = getRandomIntInclusive(100, 150);
var randy2 = getRandomIntInclusive(30, 100);

var randx3 = getRandomIntInclusive(150, 250);
var randy3 = getRandomIntInclusive(30, 100);

var randx4 = getRandomIntInclusive(-100, 50);
var randy4 = getRandomIntInclusive(30, 100);

var width = cnv.width,
    height = cnv.height,
    ratio = window.devicePixelRatio;

var x = cnv.width,
    x2 = cnv.width,
    r = 5,
    step = 0,
    step2 = 0,
    step3 = 0,
    step4 = 0,
    vx = r * 0.1;



/*var sprites = new Image();
sprites.onload = animate;
sprites.src = "./tilesets/Neo Geo NGCD - Metal Slug 3 - Rebel Biker.png";

var sprites2 = new Image();
sprites2.onload = animate;
sprites2.src = "./tilesets/Neo Geo NGCD - Metal Slug 3 - Rebel Biker.png";*/

var sprites3 = new Image();
sprites3.onload = animate;
sprites3.src = "./tilesets/advnt_full.png";

var sprites4 = new Image();
sprites4.onload = animate;
sprites4.src = "./tilesets/Neo Geo NGCD - Metal Slug - R-Shobu.png";

var sprites5 = new Image();
sprites5.onload = animate;
sprites5.src = "./tilesets/ovni.png";

var sprites6 = new Image();
sprites6.onload = animate;
sprites6.src = "./tilesets/Neo Geo NGCD - Metal Slug 3 - Rebel Biker.png";

cnv.width  = width  * ratio;
cnv.height = height * ratio;
cnv.style.width  = width  + "px";
cnv.style.height = height + "px";
cnv.imageSmoothingEnabled = false;
cnv.fillStyle = "rgba(255, 255, 255, 0.25)";

function animate() {
  draw3();
  nupdate();
  requestAnimationFrame(animate);
}

function draw3() {
  //ctx.clearRect(0, 0, cnv.width, cnv.height);
  // Affichage
  draw_sprite(x, height, r, Math.floor(step));
  draw_sprite2(x, height, r, Math.floor(step2));
  draw_sprite3(x, height, r, Math.floor(step3));
  draw_sprite4(x, height, r, Math.floor(step4));
}

function draw_sprite(x, y, r, step) {
  var s = 2;
  
  //ctx.drawImage(sprites, 66*step, 20, 66, 50, x - getRandomIntInclusive(30, 200), y - getRandomIntInclusive(30, 200), 32*s, 32*s);
  ctx.drawImage(image1, 66*step, 20, 66, 50, x - randx1*s, y - 55*s, 32*s, 32*s);
}

function draw_sprite2(x, y, r, step2) {
  var s = 2;

  ctx.drawImage(image2, 64*step2, 424, 60, 50, x - randx2*s, y - 120*s, 32*s, 32*s);
  ctx.drawImage(image3, 32*step2, 0, 32, 70, x2 - randx3*s, y - -10*s, 32*s, 32*s);
  ctx.drawImage(image4, 96*step2, 18, 88, 58, x - randx4*s, y - 150*s, 32*s, 32*s);
  ctx.drawImage(image3, 32*step2, 0, 32, 70, x2 - 50*s, y - 55*s, 32*s, 32*s);
  ctx.drawImage(image3, 32*step2, 0, 32, 70, x2 - 100*s, y - 120*s, 32*s, 32*s);
}

function draw_sprite3(x, y, r, step3) {
  var s = 2;
  
  //ctx.drawImage(sprites, 66*step, 20, 66, 50, x - getRandomIntInclusive(30, 200), y - getRandomIntInclusive(30, 200), 32*s, 32*s);
  //ctx.drawImage(sprites, 66*step3, 20, 66, 50, x - randx1*s, y - 55*s, 32*s, 32*s);
  ctx.drawImage(image6, 63*step3, 663, 52, 50, x - 150*s, y - 55*s, 32*s, 32*s);
}

function draw_sprite4(x, y, r, step4) {
  var s = 2;

  ctx.drawImage(image5, 57*step4, 0, 59, 45, x - 100*s, y - 150*s, 32*s, 32*s);
}

function nupdate() {
  // Mise à jour des variables
  x -= vx;

  x2 += vx;
  
  if (x < r || x > cnv.width - r) {
    x = 500;
    vx *= -1;
  } else if (x2 < r || x2 > cnv.width - r) {
    x2 = 500;
    vx *= 1;
  }
  
  step += 0.1;
  if (step >= 4)
      step -= 4;

  step2 += 0.1;
  if (step2 >= 7)
      step2 -= 7;

  step3 += 0.1;
  if (step3 >= 8)
      step3 -= 8;
      
  step4 += 0.1;
  if (step4 >= 6)
      step4 -= 6;
}

function removeElement(ele) {
  ele.parentNode.removeChild(ele);
}

cnv.addEventListener('click', function(event) {
  removeElement(document.getElementById("image1"));
  //removeElement(document.getElementById("myCanvas"));
  console.log("Fait");
});

window.addEventListener('keydown', keydown_fun, false);
function keydown_fun(e) {
  switch(e.code) {
    case "ArrowDown":
      cam_y += 40;
      if(cam_y > map_cnv.height-cnv.height) cam_y = map_cnv.height-cnv.height;
      break;
    case "KeyW":
    case "ArrowUp":
      cam_y -= 40;
      if(cam_y < 0) cam_y = 0;
      break;
    case "ArrowLeft":
      cam_x -= 40;
      if(cam_x < 0) cam_x = 0;
      break;
    case "ArrowRight":
      cam_x += 40;
      if(cam_x > map_cnv.width-cnv.width) cam_x = map_cnv.width-cnv.width;
      break;
  }
}

function draw() {
  ctx.beginPath();
  ctx.arc(posX, posY, ballSize, 0, 2*Math.PI);
  ctx.fillStyle = "#FF0000";
  ctx.globalAlpha = 1;
  ctx.fill();
  ctx.closePath();
}

function draw2() {

  let zoom = 1;

  let tab = all_img.length;
  //ctx.clearRect(0, 0, X, Y);
  for (let i = 0; i < Horde.length; i++) {
    if (Horde[i][0] >= 0) {
      ctx.drawImage(all_img[Horde[i][0]], Horde[i][1], Horde[i][2], 37*zoom, 45*zoom);
      Horde[i][0] += 1;
      if (Horde[i][0] == all_img.length) {
        Horde[i][0] = 0;
      } 
    }
  }
}

function onload_tilemap () {
  if(this.status == 200) {
    tilemap_loaded = 1;
    tilemap = JSON.parse(this.responseText);
    tileset = new Image();
    tileset.src = tilemap["tilesets"][0]["image"];
    tileset.onload = function() {
      tileset_loaded = 1;
      let tileset_i = 1;
      let tileset_j = 1;
      let tileset_imageheight = tilemap["tilesets"][0]["imageheight"];
      let tileset_imagewidth = tilemap["tilesets"][0]["imagewidth"];
      let tileset_margin = tilemap["tilesets"][0]["margin"];
      let tileset_spacing = tilemap["tilesets"][0]["spacing"];
      let tileset_tileheight = tilemap["tilesets"][0]["tileheight"];
      let tileset_tilecount = tilemap["tilesets"][0]["tilecount"];
      let map_height = tilemap["height"];
      let map_width = tilemap["width"];
      map_cnv.height = map_height*tileset_tileheight;
      map_cnv.width = map_width*tileset_tileheight;
      let map_ctx = map_cnv.getContext("2d");

      let layer0_data = tilemap["layers"][0]["data"];
      let layer0_height = tilemap["layers"][0]["height"];
      let layer0_width = tilemap["layers"][0]["width"];

      let layer1_data = tilemap["layers"][1]["data"];
      let layer1_height = tilemap["layers"][1]["height"];
      let layer1_width = tilemap["layers"][1]["width"];

      let layer2_data = tilemap["layers"][2]["data"];
      let layer2_height = tilemap["layers"][2]["height"];
      let layer2_width = tilemap["layers"][2]["width"];

      console.log(tileset_imageheight);
      console.log(tileset_imagewidth);
      console.log(tileset_tileheight);
      console.log(map_height);
      console.log(map_width);
//      console.log(layer0_data);
//      console.log(layer0_height);
//      console.log(layer0_width);

      let canvas = document.createElement('canvas');
      canvas.height = tileset_imageheight;
      canvas.width = tileset_imageheight;
      let context = canvas.getContext('2d');
      //ctx.drawImage(tileset, 0, 0, tileset.width, tileset.height);
      context.drawImage(tileset, 0, 0, tileset.width, tileset.height);
      let ih = 1;
      for(let ih = 1, nh = tileset_imageheight; ih < nh; ih += (tileset_tileheight+2)) {
        for(let iw = 1, nw = tileset_imagewidth; iw < nw; iw += (tileset_tileheight+2)) {
          let canvas2 = document.createElement('canvas');
          canvas2.height = tileset_tileheight;
          canvas2.width = tileset_tileheight;
          let context2 = canvas2.getContext('2d');
          let canvasImageData = context.getImageData(iw, ih, tileset_tileheight, tileset_tileheight);
          let canvasData = canvasImageData.data;
          let canvasImageData2 = context2.getImageData(0, 0, tileset_tileheight, tileset_tileheight);
          let canvasData2 = canvasImageData2.data;
          for(let i = 0, n = canvasData.length; i < n; i += 4) {
            canvasData2[i] = canvasData[i];
            canvasData2[i + 1] = canvasData[i + 1];
            canvasData2[i + 2] = canvasData[i + 2];
            canvasData2[i + 3] = canvasData[i + 3];
          }
          context2.putImageData(canvasImageData2, 0,0);
          tileset_elts.push(canvas2);
        }
      }
//      console.log(layer0_data[0]);
//      console.log(layer0_data[1]);

      let layer0_data_i = 0;
      for(let ih = 0, nh = layer0_height; ih < nh; ih += 1) {
        for(let iw = 0, nw = layer0_width; iw < nw; iw += 1) {
          if(layer0_data[layer0_data_i] > 0) {
            map_ctx.drawImage(tileset_elts[layer0_data[layer0_data_i]-1], iw*tileset_tileheight, ih*tileset_tileheight);
          }
          layer0_data_i += 1;
        }
      }
      let layer1_data_i = 0;
      for(let ih = 4, nh = layer1_height; ih < nh; ih += 1) {
        for(let iw = 0, nw = layer1_width; iw < nw; iw += 1) {
          if(layer1_data[layer1_data_i] > 0) {
            map_ctx.drawImage(tileset_elts[layer1_data[layer1_data_i]-1], iw*tileset_tileheight, ih*tileset_tileheight);
          }
          layer1_data_i += 1;
        }
      }
      let layer2_data_i = 0;
      for(let ih = 8, nh = layer2_height; ih < nh; ih += 1) {
        for(let iw = 0, nw = layer2_width; iw < nw; iw += 1) {
          if(layer2_data[layer2_data_i] > 0) {
            map_ctx.drawImage(tileset_elts[layer2_data[layer2_data_i]-1], iw*tileset_tileheight, ih*tileset_tileheight);
          }
          layer2_data_i += 1;
        }
      }

    }
  }
}

function update_pos () {
  if (nbmax < nbr) {
    let y_= Math.random() * 530;
    Horde.push([0, -50, y_]);
    nbmax++;
    //nbr++;
  }
  for (let i = 0; i < Horde.length; i++) {
    Horde[i][1] += 4;
    if (Horde > 500) {
      Horde[i][1] = -60;
      nbr *=2;
    }
  }
}

let xobj = new XMLHttpRequest();
xobj.onload = onload_tilemap;
xobj.overrideMimeType("application/json");
xobj.open("GET", "./tilemaps/operation-game.json", true);
xobj.send();

let COUNT = 0;
function update(timestamp) {
  /*cam_x += 1;
  if(cam_x > map_cnv.width-cnv.width) cam_x = map_cnv.width-cnv.width;*/
  if(tilemap_loaded == 1 && tileset_loaded == 1) {
    //print();
    let map_ctx = map_cnv.getContext("2d");
    let imageData = map_ctx.getImageData(cam_x, cam_y, cnv.width, cnv.height);
    ctx.putImageData(imageData, 0,0);
    update_pos();
    //draw();
    //draw2();
    requestAnimationFrame(update);
  } else {
    requestAnimationFrame(update);
  }
}

document.addEventListener("mousemove", mousemove_fun);
function mousemove_fun(e) {
  posX = e.clientX;
  posY = e.clientY;
}
requestAnimationFrame(update);
