all:
	@$(MAKE) -s -C serial
	@$(MAKE) -s -C showme
	@$(MAKE) -s -C parallel

clean:
	$(MAKE) clean -C serial
	$(MAKE) clean -C showme
	$(MAKE) clean -C parallel
	