{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "hello.cc" ]
    },
	    'conditions': [
			['OS=="linux"', {
		        'cflags!': [ '-fno-exceptions', '-fno-rtti'],
		        'cflags': ['-fexceptions', '-fopenmp', '-std=c++11'],
	        }],
	        ['OS=="windows"', {
		        'cflags!': [ '-fno-exceptions', '-fno-rtti'],
		        'cflags': ['-fexceptions', '-fopenmp', '-std=c++11'],
	        }]
		]
  ]
}