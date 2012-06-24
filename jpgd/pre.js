Module['preRun'] = function() {
    FS.createDataFile(
      '/',
      'input.jpg',
      Module['intArrayFromString'](Module['data']),
      true,
      true);
  };
Module['arguments'] = [''];
Module['return'] = '';
  Module['print'] = function(text) {
    Module['return'] += text + '\n';
  };

