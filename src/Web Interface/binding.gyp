{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "hello.cc" ],
      'cflags!': [ '-fno-exceptions', '-fno-rtti'],
	  'cflags': ['-fexceptions', '-fopenmp', '-std=c++11'],
    }
  ]
}