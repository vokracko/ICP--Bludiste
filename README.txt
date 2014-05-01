Projekt do předmětu ICP v roce 2014
	Cílem bylo vytvořit síťovou hru s topologií klient/server.
	Jedná se o hru bludiště s limitem čtyř hráčů v jedné hře.
	Vyhrává hráč, který jako první projde branou. Bránu je nejprve potřeba otevřit, což může pouze hráč, který vlastní klíč.
	Obtížnost hry zvyšuje právě jeden hlídač.
	Hru je možné hrát jak v grafickém tak v konzolovém režimu.
	Pro klienta jsou vytvořeny spustitelné soubory bludiste2014 a bludiste2014-cli v adresáři examples.
	Server komunikuje na portu 1234 a umožňuje vytvoření neomezeného počtu her a připojení libovolného počtu klientů, k čemuž využívá vlákna.

	Ovládání hry:
		left - otočení doleva
		right - otočení doprava
		take - získání klíče
		open - otevření brány
		go - pohyb vpřed
		stop - zastavení pohybu
		step - jeden krok vpřed

Autoři:
	xvesel63 Michal Veselý
	xvokra00 Lukáš Vokráčko


