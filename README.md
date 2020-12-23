# 3D_AddPrint

We propose a converter image to gcode based on freeman image processing. 
We extract from the input image a freeman chain used subsequently to generate the g-code corresponding to the input image.

## C++ compile :

`$ cmake . && cmake --build . --target $target`

## C++ Run :

`$ ./slice Map.png'

## Result Exemples
The results should look like as following examples :

### Gear

#### Image
<img src="https://drive.google.com/uc?export=view&id=14k2V2uVd28rjAFLCuIaeH_TUYjLjpM9O">

#### Freeman
<img src="https://drive.google.com/uc?export=view&id=1npeulbjtMrCnGPED7xT6uSA008lJOLIU0">

#### Gcode simulation
<img src="https://drive.google.com/uc?export=view&id=149auagA2LtoOhls7wQ4e3TEqWfMXmGoQ">

### Map

#### Image
<img src="https://drive.google.com/uc?export=view&id=141MKkJrwbSIlVMAnIYvVrM-w5H2iIegI" width="600" height="500">

#### Gcode simulation
<img src="https://drive.google.com/uc?export=view&id=1qprwG7bHuOjpHwnj8jh5MK_rj7jlpC0g" width="600" height="500">
