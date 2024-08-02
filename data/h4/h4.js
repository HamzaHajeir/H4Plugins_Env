let ws
let w
let colortable=["red","orange","yellow","green","blue","bi"]
const RECORD_SEPARATOR="|"
const UNIT_SEPARATOR="~"

class WebSocketEventManager {
    constructor() {
        this.listeners = {};
        this.cbmessage = null;
    }
    hook(type, cb) {
        if (!this.listeners[type]) {
            this.listeners[type] = [];
        }
        this.listeners[type].push(cb);
    }
    unhook(type, cb) {
        const listeners = this.listeners[type];
        if (listeners) {
            this.listeners[type] = listeners.filter(listener => listener !== cb);
        }
    }
    onmessage(cb) {
        this.cbmessage = cb;
    }
    handle(msg) {
        const parts = msg.split(",");
        const type = parts[0];
        const data = parts.slice(1).join(",");

        if (type === '') {
            if (this.cbmessage) {
                this.cbmessage(data);
            }
        } else {
            this.handleEvent(type, data);
        }
    }
    handleEvent(eventType, data) {
        const listeners = this.listeners[eventType] || [];
        listeners.forEach(listener => {
            if (typeof listener === 'function') {
                listener(data);
            }
        });
    }
}

function toaster(t){
    msg.innerHTML=t;
    setTimeout(function () { msg.innerHTML="&nbsp;"; },30000);
}

function send(url){
    document.body.style.cursor = "wait";
    toaster("&nbsp;");
    w.send(url);
}

function properCase(s){ return s.split(" ").map(function (x){ return x.charAt(0).toUpperCase() + x.slice(1) }).join(" ") }

function makeTitle(i,cl){
    let e=document.createElement("div");
    e.classList="title "+cl;
    e.innerHTML=properCase(i)
    return e;
}

function makeBaseValueNode(id,type,cl,f){
    let n=document.createElement(type);
    n.id=id;
    if(cl.length) n.classList=cl;
    ws.hook(id, (e) => f(document.getElementById(id),e) )
    return n;
}

function sendvalue(e){ send("h4/config/"+e.target.id+"=`"+e.target.value+"`") }

function btnImg(n,v){ n.src="/"+n.id+parseInt(v)+".jpg" }

function options(elem,value){
    elem.innerHTML="";
    let opts=value.split(RECORD_SEPARATOR)
    opts.sort()
    opts.forEach(function(e){
        let kv=e.split(UNIT_SEPARATOR);
        let opt=document.createElement("option");
        opt.value=kv[1];
        opt.innerHTML=kv[0];
        elem.appendChild(opt);
    })
}

function makeValue(id,type,active,color,value){
    let valueNode;
    let imgNode;
    switch(type){
        case 0: // TEXT
            valueNode=makeBaseValueNode(id,"div","uv",(n,e) => n.innerHTML=e )
            valueNode.innerHTML=value;
            break;
        case 1: // GPIO
        case 2: // BOOL
            let hue=colortable[color];
            valueNode=makeBaseValueNode(id,"div","ld led-"+hue+"-"+parseInt(value),(n,e) => {
                let b=parseInt(e)
                let C="led-"+hue+"-";
                n.classList.remove(C+(b ? 0:1));
                n.classList.add(C+b);
            })
            break;
        case 3: // input
            valueNode=makeBaseValueNode(id,"input","",(n,e) => { n.value=e })
            valueNode.type="text";
            valueNode.value=value;
            valueNode.addEventListener("focus", (e) => e.target.classList.add("edit") )
            valueNode.addEventListener("blur",  (e) => {
                let n=document.getElementById(e.target.id);
                if(n.value!=value) sendvalue(e)
                else n.classList.remove("edit")
            })
            break;
        case 4: // image button
            imgnode=makeBaseValueNode(id,"input","",(n,e) => btnImg(n,e) )
            imgnode.type="image";
            btnImg(imgnode,value);
            imgnode.addEventListener("click", (e) => {
                let n=document.getElementById(e.target.id);
                let v=parseInt(n.src.replace(".jpg","").slice(-1))
                send("h4/config/"+n.id+"="+(v ? 0:1))
            })
            valueNode=document.createElement("div")
            valueNode.classList="bouter"
            let binner=document.createElement("div")
            binner.classList="binner"
            binner.appendChild(imgnode)
            valueNode.appendChild(binner)
            break;
        case 5: // dropdown
            valueNode=makeBaseValueNode(id,"select","",(n,e) => options(n,e) )
            options(valueNode,value)
            valueNode.addEventListener("change", (e) => sendvalue(e) )
            break;
        case 6: // image
            valueNode=document.createElement("div")
            valueNode.classList="bouter"
            imgnode=document.createElement("img");
            imgnode.id=id;
            imgnode.src=value;
            valueNode.appendChild(imgnode)
            ws.hook(id, (e) => document.getElementById(id).src=e )
            break;
        default:
            valueNode=makeBaseValueNode(id,"div","uv");
            valueNode.innerHTML="NYI "+value;
    }
    return valueNode;
}

function ui2(d){
    let parts=d.split(",")
    let id=parts[0]
    if(!document.getElementById(id)){
        let type=parseInt(parts[1])
        let hanger=document.getElementById(parts[2]+"hang")
        hanger.style="display: grid" // light 'em up (unused stays invisible)
        let active=parseInt(parts[3])
        let color=parts[4]
        let value=parts.slice(5).join(",")
        if(type==4 || type==6) hanger.insertBefore(makeValue(id,type,active,color,value),null) // img button = full-width
        else {
            hanger.insertBefore(makeTitle(id,active ? "tuia":""),null)
            hanger.insertBefore(makeValue(id,type,active,color,value),null)
        }
}
}

document.addEventListener("DOMContentLoaded", function() {
    if (!!window.WebSocket) { 
        ws = new WebSocketEventManager();
        proto = "ws"
        if (document.location.protocol === 'https:') {
            proto="wss"
        }
        w = new WebSocket(proto+"://"+document.location.host+"/ws");
        w.onerror = function(e) {
            console.warn(e);
            document.querySelectorAll('div.hanger').forEach((d) => d.style.background="#ff0000")
            toaster("Error "+e)
        };
        w.onopen = function() { 
            // ws.send("Hello there!");
            toaster("Connection open")
        };
        w.onmessage = function (evt) {
            ws.handle(evt.data);
        };
        w.onclose = function() { toaster("Connection closed") }
    } else { console.error("WebSocket isn't supported in this browser") }

    let rr=document.getElementById("reply")
    let cmd=document.getElementById("cmd")
    let msg=document.getElementById("msg")

    ws.hook('ui', function(e){ ui2(e) });
    ws.onmessage((e)=>{ toaster(e) });

    ws.hook('reply', (resp)=>{
        let r=document.getElementById("reply")
        document.body.style.cursor = "default";
        r.innerHTML=""
        r.style.color="#ffffff" // css
        var j=JSON.parse(resp);
        if(j.res) toaster("Error: "+j.res+" "+j.msg)
        else {
            j.lines.forEach(function(l){ r.innerHTML+=l+'\n'})
            document.querySelectorAll("input.edit").forEach(x => x.classList.remove("edit") )
        }
    })

    toaster("Thank you for using H4/Plugins - please support me on Patreon, see link below");

    document.getElementById("cc").addEventListener('submit', function(e){
        e.preventDefault();
        send(cmd.value);
    },{capture: true});

    rr.addEventListener('click', function(e){
        let lines=rr.value.split("\n")
        let n=rr.value.substr(0, rr.selectionStart).split("\n").length
        cmd.value=lines[n-1]
        send(lines[n-1])
    },{capture: true});

    document.getElementById("qh").addEventListener('click', function(e){ send("help") },{capture: true});
})