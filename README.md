# Emscripten file.data parser

Emscripten compiles all static files into a single `file.data` file. From documentation https://emscripten.org/docs/porting/files/packaging_files.html

```shell
emcc file.cpp -o file.html --preload-file asset_dir
```

        The command generates file.html, file.js and file.data. The .data file contains all the files in asset_dir/, and is loaded by file.js.

If you have two files, `asset_dir/file01.png` and `asset_dir/file02.png`, their bytes will be joined into a single file `file.data`. The file `file.js` will contain a `load` funtion that tells the original file name, start byte, end byte and if it is audio.

```js
loadPackage({"files":[{"filename":"/asset_dir/file01.png","start":0,"end":12345,"audio":0},{"filename":"/asset_dir/file02.png","start":12345,"end":67890,"audio":0}],"remote_package_size":67890,"package_uuid":"xyz-123"})
```

We just have to read `file.data` (as bytes) for each start/end and save as a new file (as bytes). Make sure to create the correct folder structure.
