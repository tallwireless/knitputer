####
#
# Make file to make my life easier
#
#####


clean:
	pio run -t clean

build:
	pio run

upload:
	pio run -t upload

monitor:
	pio run -t monitor
