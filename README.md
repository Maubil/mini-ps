# mini-ps
Small, portable and very basic ps utility

# why ?
containers are mostly stripped down to the minimum, meaning there's no ps tool. Investigating those containers without ps makes it even worse.

with this, you can either build or download the binary and mount/upload/whatever to the container.
or, if curl of wget is available -> `curl -LO https://github.com/Maubil/mini-ps/releases/download/v0.1/ps-mini && chmod +x ps-mini && ps-mini`
