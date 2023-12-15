La práctica 5 esta realizada sobre la 4, por lo que lo que se ha añadido son homologos de los generadores, forceregistry
y fuerzas usando rigidbody, que es la clase nueva e interesante.
El rigidbody esta construido con la particula como base, pero al contrario que esta, en vez de recibir masa, volumen, etc...,
recibe una densidad y la constructora se encarga de crear el objeto, que contiene myRigid, un rigidb body dinámico de la 
libreria physx. A partir de eso funciona exactamente como una particula a la que se le añaden las fuerzas con un addforce, que simplemente
es un wrapper para añadir la fuerza al rigid body del objeto.
En la escena esta activo el generador de rigid bodies y el generador de viento para que se vea como afectan las fuerzas.
Para eliminar esto y ver mejor la explosion, hay que comentar la creacion del windGenerator.
La explosión se activa mediante un evento de teclado con la letra E que activa el generador de explosiones que a su vez aplica fuerza
según su fórmula y pasado el tiempo definido en su constructora, se desactiva.