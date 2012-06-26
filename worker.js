importScripts('djpeg.js');

onmessage = function(event) {
	var data = readJpeg(event.data);

	var b = new ArrayBuffer(2048*2048*4);
    var v1 = new Uint8Array(b);
    
    var i = 0,
        j = 18;
    while (i < 2048*2048*4 && j < (2048*2048*3)+18) {
        v1[i] = data[j + 2]; // R
        v1[i + 1] = data[j + 1]; // G
        v1[i + 2] = data[j]; // B
        v1[i + 3] = 255; // A
        // Next pixel
        i += 4;
        j += 3;
    }

	postMessage(v1);
};
