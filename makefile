# Run make on each subdirectory
# http://stackoverflow.com/questions/17834582/run-make-in-each-subdirectory
Folder_Lambda = lambda
Folder_Iterator = iterator

.PHONY: project_code

project_code:
	$(MAKE) -C $(Folder_Lambda)
	$(MAKE) -C $(Folder_Iterator)

clean:
	$(MAKE) -C $(Folder_Lambda) clean	
	$(MAKE) -C $(Folder_Iterator) clean

mrproper:
	$(MAKE) -C $(Folder_Lambda) mrproper	
	$(MAKE) -C $(Folder_Iterator) mrproper

run:
	$(MAKE) -C $(Folder_Lambda) run	
	$(MAKE) -C $(Folder_Iterator) run
