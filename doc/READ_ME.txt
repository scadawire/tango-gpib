Version_1_12_03 :



Cette version contient l'écriture et la lecture de données binaires.



Les methodes sont :



	_ send_bin_data(const Tango::DevVarCharArray *binary_data_to_send)

	_ Tango::DevVarCharArray receive_bin_data (Tango::DevUShort nb_binary_data_to_receive)



	_ resetState( ) : remise a 0 des variables globales ibsta, iberr et ibcntl.







Mise a jour de ibsta, iberr et ibcntl :



	saveState( ) : utilisation de ThreadIbsta, ThreadIberr, ThreadIbcntl pour mettre à jour

			ibsta, iberr et ibcntl.

	Selon la doc de National Instruments, dans une application multithread il est preferable

		d'utiliser ces thread pour mettre a jour ces trois variables globales !







LIMITATION :



	gestion du caractere de fin de chaine EOS.

	





Probleme :

	getConnectedDeviceList ne me retourne pas la liste des devices. 

	Il m'informe (dans Jive) que la taille de l'array = 0 !!?

	Je regarde aussi de mon cote, peut-etre que j'ai casse qqchose.



