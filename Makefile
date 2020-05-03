all:
	@$(MAKE) -s -C serial
	@$(MAKE) -s -C showme

clean:
	$(MAKE) clean -C serial
	$(MAKE) clean -C showme