self.onmessage = function(event){

	var b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
	var outputStr = "";
	var i = 0;

	while (i < event.data.length) {
		//all three "& 0xff" added below are there to fix a known bug 
		//with bytes returned by xhr.responseText
		var byte1 = event.data.charCodeAt(i++) & 0xff;
		var byte2 = event.data.charCodeAt(i++) & 0xff;
		var byte3 = event.data.charCodeAt(i++) & 0xff;

		var enc1 = byte1 >> 2;
		var enc2 = ((byte1 & 3) << 4) | (byte2 >> 4);

		var enc3, enc4;
		if (isNaN(byte2)) {
			enc3 = enc4 = 64;
		} else {
			enc3 = ((byte2 & 15) << 2) | (byte3 >> 6);
			if (isNaN(byte3)) {
				enc4 = 64;
			} else {
				enc4 = byte3 & 63;
			}
		}
		outputStr += b64.charAt(enc1) + b64.charAt(enc2) + b64.charAt(enc3) + b64.charAt(enc4);
	}

	self.postMessage(outputStr);
	self.close();
}
