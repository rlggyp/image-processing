Praktikum 5: Applying erotion and dilation on binary image
===
How to build
---
```bash
mkdir build && cd build
cmake ../

make
```

Run the executable
---
```bash
./praktikum5
```

Input
---
### Soccer Ball
![Soccer Ball](../img/soccer_ball_green_bg.jpg)

Result
---
### Masking Result
<div style="display: flex;">
  <div style="flex: 50%; padding: 5px;">
    <img src="../img/soccer_ball_green_bg.jpg" alt="Input" style="width: 100%;">
  </div>
  <div style="flex: 50%; padding: 5px;">
    <img src="https://i.imgur.com/I6UutpQ.jpg" alt="Binary Image" style="width: 100%;">
  </div>
</div>

### Erotion Result
<div style="display: flex;">
  <div style="flex: 50%; padding: 5px;">
    <img src="https://i.imgur.com/zzNatli.jpg" alt="Binary Image" style="width: 100%;">
  </div>
  <div style="flex: 50%; padding: 5px;">
    <img src="https://i.imgur.com/u3ragJ8.jpg" alt="Result" style="width: 100%;">
  </div>
</div>

### Dilation Result
<div style="display: flex;">
  <div style="flex: 50%; padding: 5px;">
    <img src="https://i.imgur.com/UHxGScr.jpg" alt="Binary Image" style="width: 100%;">
  </div>
  <div style="flex: 50%; padding: 5px;">
    <img src="https://i.imgur.com/ZS5ELMJ.jpg" alt="Result" style="width: 100%;">
  </div>
</div>


### Dilation + Erotion
<div style="display: flex;">
  <div style="flex: 50%; padding: 5px;">
    <img src="https://i.imgur.com/5HObVcT.jpg" alt="Binary Image" style="width: 100%;">
  </div>
  <div style="flex: 50%; padding: 5px;">
    <img src="https://i.imgur.com/cGYpg11.jpg" alt="Result" style="width: 100%;">
  </div>
</div>