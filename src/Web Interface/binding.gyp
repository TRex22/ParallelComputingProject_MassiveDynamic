{
  "targets": [
    {
      "target_name": "test",
      "sources": [ "test.cpp" ],
      'cflags!': [ '-fno-exceptions', '-fno-rtti'],
	  'cflags': ['-fexceptions', '-fopenmp', '-std=c++11'],
    }
  ]
}