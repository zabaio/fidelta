all:
	@$(MAKE) -s -C software
	@$(MAKE) -s -C showme

clean:
	$(MAKE) clean -C software
	$(MAKE) clean -C showme
	
