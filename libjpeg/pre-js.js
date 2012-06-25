Module['preRun'] = function() {
	try {
		FS.deleteFile('/input.jpg');
	} catch (e) {};
	FS.createDataFile('/', 'input.jpg', Module['data'], true, false);
};
Module['arguments'] = ['-targa', '-fast', '-outfile', 'output.bin', 'input.jpg'];

Module['print'] = function(text) {
	Module['return'] += text + '\n';
};
