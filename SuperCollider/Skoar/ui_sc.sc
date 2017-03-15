SkoarUiSuperCollider : SkoarUiView {

    var btn_server;
    var btn_settings;

    init {
        view = View();

        btn_server = SkoarUiButton("Server", Color.gray(0.5), Color.black, Color.gray(0.5), {
            this.boot_server;
        });

        if (Server.default.serverRunning == true) {
            this.server_up;
        };

        btn_settings = SkoarUiButton("Settings", Color.gray(0.5), Color.black, Color.gray(0.5), {
            log.i("settings not implemented");
        });

        layout = HLayout(
            btn_server.view,
            btn_settings.view
        );

        view.layout = layout;
    }

    server_booting {
        btn_server.view.string = "booting...";
        btn_server.colour = Color.blue(1);
    }

    server_up {
        btn_server.view.string = "server up";
        btn_server.colour = Color.green(0.7);
    }

    server_down {
        btn_server.view.string = "server down";
        btn_server.colour = Color.red(0.7);
    }

    server_killing {
        btn_server.view.string = "killing...";
        btn_server.colour = Color.magenta(0.7);
    }

    kill_servers {
		log.i("Killing zombie scsynths, waiting 10 seconds.");
		this.server_killing;
		try {
			Server.killAll;
			//"killall scsynth".unixCmd;
			//"killall -9 scsynth".unixCmd;
		} {
			| error |
			log.e("killing zombie server failed.");
		};

		10.wait;
	}

    boot_server {
        Routine({
            this.boot_server_first;
        }).play(AppClock);
    }

    boot_server_first {
		var s = Server.default;
		var c = Condition.new;

		log.d("Server booting.");
		this.server_booting;

		c.test = false;
		s.waitForBoot(
			onComplete: {
			    2.wait;

				case {s.hasShmInterface.not} {
				    log.w("Shared memory problem, will try killing.");
					this.kill_servers;
					this.boot_server_final(c);

				} {s.serverRunning.not} {
				    log.w("Server failed to boot. will try killing.");
					this.kill_servers;
					this.boot_server_final(c);
				} {
				    this.server_up;
					c.test = true;
					c.signal;
				};

			},

			onFailure: {
				log.w("server failed to boot. will try killing.");

				this.kill_servers;

				// try one more time
				this.boot_server_final(c);
				true
			}
		);

		c.wait;

		log.d("Server booted.");
		^s
	}

	boot_server_final {
		| c |
		var s = Server.default;

		log.d("Server booting, second try.");
        this.server_booting;

        s.waitForBoot(
			onComplete: {
                2.wait;

				case {s.hasShmInterface.not} {
				    log.e("Shared memory problem, try quitting everything.");

				} {s.serverRunning.not} {
				    log.e("Server failed to boot again.");

				} {
				    this.server_up;
					c.test = true;
					c.signal;
				};

			},

			onFailure: {
				log.e("server failed to boot.");
				this.server_down;
				true
			}
		);
	}
}