# lockless_pubsub
Publisher Subscriber framework using lock less ring buffer

Steps to Setup SPDK and run the code.

1. First build SPDK static library using the steps mentioned in the link--

https://github.com/spdk/spdk

Or Run below commands in order

	git clone https://github.com/spdk/spdk

	cd spdk

	git submodule update --init

The dependencies can be installed automatically by scripts/pkgdep.sh.

	./scripts/pkgdep.sh

to build run below commands

	./configure
	
	make

run unit test to make sure build is successful using below command

	./test/unit/unittest.sh


before running spdk application, allocate hugepages using below command

	sudo scripts/setup.sh


2. Then paste the code folder in spdk/examples/ directory

3. replace the file "spdk.common.mk " in spdk/mk/ directory with the given one

4. now from the code folder open terminal-
	- run "make" to compile code
	- run "sudo ./driver" to see the output
