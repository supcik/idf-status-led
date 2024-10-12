PATH:="get_started"

build:
    idf.py build --project-dir status_led/examples/{{PATH}}

flash:
    idf.py flash --project-dir status_led/examples/{{PATH}}

monitor:
    idf.py monitor --project-dir status_led/examples/{{PATH}}

menuconfig:
    idf.py menuconfig --project-dir status_led/examples/{{PATH}}

set-target TARGET='esp32s3':
    idf.py set-target --project-dir status_led/examples/{{PATH}} {{TARGET}}

clean:
    idf.py fullclean --project-dir status_led/examples/{{PATH}}

save-defconfig:
    idf.py save-defconfig --project-dir status_led/examples/{{PATH}}

update-settings:
     jq '."idf.buildPath"|="${workspaceFolder}/status_led/examples/{{PATH}}/build"' ./.vscode/settings.json
