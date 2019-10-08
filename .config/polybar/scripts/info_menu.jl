if !isfile("/tmp/info_menu.json")
  f=open("/tmp/info_menu.json", "w");
  write(f,"state : NONE");
  close(f);
end
f=open("/tmp/info_menu.json", "r");
state = read(f,String)[9:end];
print(state);
close(f)
print(state=="NONE");
if state=="NONE"
  print("test")
elseif state == "DRIVES"
  disks = ("df -h | grep ^/dev",String)
  spliteddisks = split(disks,"\n")
  diskname=""
  diskpercentage=0
  for disk in spliteddisks
    diskname = split(disk," ")[end]
    diskpercentage = split(disk," ")[end-1][1:2]
    print(diskname)
    print(diskpercentage)
  end

end
