 * Copyright (c) 2000-2012 Apple Inc. All rights reserved.



__private_extern__ int unlink1(vfs_context_t, struct nameidata *, int);
		/* disable preflight only for udf, a hack to be removed after 4073176 is fixed */
		if (vp->v_tag == VT_UDF)
			return 0;
		if ((flags & SKIPSYSTEM) && ((vp->v_flag & VSYSTEM) ||
            (vp->v_flag & VNOFLUSH)))
		if ((flags & WRITECLOSE) &&
            (vp->v_writecount == 0 || vp->v_type != VREG)) 
        if (((vp->v_usecount != 0) &&
            ((vp->v_usecount - vp->v_kusecount) != 0))) 
			return(1);
	return(0);
	
		return(ENOENT);
		if (flags & LK_NOWAIT)
			return (ENOENT);

		mount_lock(mp);

		if (mp->mnt_lflag & MNT_LDEAD) {
		        return(ENOENT);
		}
		if (mp->mnt_lflag & MNT_LUNMOUNT) {
		        mp->mnt_lflag |= MNT_LWAIT;
			/*
			 * Since all busy locks are shared except the exclusive
			 * lock granted when unmounting, the only place that a
			 * wakeup needs to be done is at the release of the
			 * exclusive lock at the end of dounmount.
			 */
			msleep((caddr_t)mp, &mp->mnt_mlock, (PVFS | PDROP), "vfsbusy", NULL);
		mount_unlock(mp);
	 * until we are granted the rwlock, it's possible for the mount point to
	 * change state, so reevaluate before granting the vfs_busy

	strncpy(mp->mnt_vfsstat.f_fstypename, vfsp->vfc_name, MFSTYPENAMELEN);
		if (vfsp->vfc_mountroot == NULL)
		if ((error = (*vfsp->vfc_mountroot)(mp, rootvp, ctx)) == 0) {
	mount_t nmp;
	TAILQ_FOREACH(nmp, &mountlist, mnt_list) {
		while (vfs_getvfs_locked(&tfsid)) {
			if (++mntid_gen == 0)
				mntid_gen++;
			tfsid.val[0] = makedev(nblkdev + mtype, mntid_gen);
		}
static boolean_t
	        if (--vp->v_writecount < 0)
		        panic("vnode_rele_ext: vp %p writecount -ve : %d.  v_tag = %d, v_type = %d, v_flag = %x.", vp,  vp->v_writecount, vp->v_tag, vp->v_type, vp->v_flag);
	        /*
	        if (vp->v_usecount == 0) {
	                vp->v_lflag |= VL_NEEDINACTIVE;
	if ( (vp->v_lflag & (VL_TERMINATE | VL_DEAD)) || dont_reenter) {
	        /*
		 * the filesystem on this release... in
		 * this case, we'll mark the vnode aged
		 * if it's been marked for termination
	        if (dont_reenter) {
		        if ( !(vp->v_lflag & (VL_TERMINATE | VL_DEAD | VL_MARKTERM)) ) {
			        vp->v_lflag |= VL_NEEDINACTIVE;
				if (vnode_on_reliable_media(vp) == FALSE) {
	        vnode_list_add(vp);
#if 0
struct ctldebug debug1 = { "busyprt", &busyprt };
#endif /* 0 */
		if ((vp->v_id != vid) || ((vp->v_lflag & (VL_DEAD | VL_TERMINATE)))) {
	/*
	 * remove the vnode from any mount list
	 * it might be on...
	 */
	insmntque(vp, (struct mount *)0);

		        VNOP_FSYNC(vp, MNT_WAIT, ctx);
			buf_invalidateblks(vp, BUF_WRITE_DATA | BUF_INVALIDATE_LOCKED, 0, 0);
			vnode_relenamedstream(pvp, vp, ctx);
				vnode_reclaim_internal(vq, 0, 1, 0);
				vnode_put(vq);
	vnode_reclaim_internal(vp, 0, 0, REVOKEALL);
__private_extern__ int
is_package_name(const char *name, int len)
vfs_sysctl(int *name, u_int namelen, user_addr_t oldp, size_t *oldlenp, 
           user_addr_t newp, size_t newlen, proc_t p)
	struct vfstable *vfsp;
	int *username;
	u_int usernamelen;
	int error;
	struct vfsconf vfsc;
	if (namelen > CTL_MAXNAME) {
		return (EINVAL);
	}
	/* All non VFS_GENERIC and in VFS_GENERIC, 
	 * VFS_MAXTYPENUM, VFS_CONF, VFS_SET_PACKAGE_EXTS
	 * needs to have root priv to have modifiers. 
	 * For rest the userland_sysctl(CTLFLAG_ANYBODY) would cover.
	 */
	if ((newp != USER_ADDR_NULL) && ((name[0] != VFS_GENERIC) || 
			((name[1] == VFS_MAXTYPENUM) ||
			 (name[1] == VFS_CONF) ||
			 (name[1] == VFS_SET_PACKAGE_EXTS)))
	     && (error = suser(kauth_cred_get(), &p->p_acflag))) {
			return(error);
	}
	/*
	 * The VFS_NUMMNTOPS shouldn't be at name[0] since
	 * is a VFS generic variable. So now we must check
	 * namelen so we don't end up covering any UFS
	 * variables (sinc UFS vfc_typenum is 1).
	 *
	 * It should have been:
	 *    name[0]:  VFS_GENERIC
	 *    name[1]:  VFS_NUMMNTOPS
	 */
	if (namelen == 1 && name[0] == VFS_NUMMNTOPS) {
		return (sysctl_rdint(oldp, oldlenp, newp, vfs_nummntops));
	}
	/* all sysctl names at this level are at least name and field */
	if (namelen < 2)
		return (EISDIR);		/* overloaded */
	if (name[0] != VFS_GENERIC) {
		mount_list_lock();
		for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next) 
			if (vfsp->vfc_typenum == name[0]) {
				vfsp->vfc_refcount++;
				break;
			}
		mount_list_unlock();
		if (vfsp == NULL)
			return (ENOTSUP);
		/* XXX current context proxy for proc p? */
		error = ((*vfsp->vfc_vfsops->vfs_sysctl)(&name[1], namelen - 1,
		            oldp, oldlenp, newp, newlen,
			    vfs_context_current()));
		mount_list_lock();
		vfsp->vfc_refcount--;
		mount_list_unlock();
		return error;
	switch (name[1]) {
	case VFS_MAXTYPENUM:
		return (sysctl_rdint(oldp, oldlenp, newp, maxvfsconf));
	case VFS_CONF:
		if (namelen < 3)
			return (ENOTDIR);	/* overloaded */
		mount_list_lock();
		for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
			if (vfsp->vfc_typenum == name[2])
				break;
		if (vfsp == NULL) {
			mount_list_unlock();
			return (ENOTSUP);
		}
		vfsc.vfc_reserved1 = 0;
		bcopy(vfsp->vfc_name, vfsc.vfc_name, sizeof(vfsc.vfc_name));
		vfsc.vfc_typenum = vfsp->vfc_typenum;
		vfsc.vfc_refcount = vfsp->vfc_refcount;
		vfsc.vfc_flags = vfsp->vfc_flags;
		vfsc.vfc_reserved2 = 0;
		vfsc.vfc_reserved3 = 0;
		mount_list_unlock();
		return (sysctl_rdstruct(oldp, oldlenp, newp, &vfsc,
					sizeof(struct vfsconf)));
		
	case VFS_SET_PACKAGE_EXTS:
	        return set_package_extensions_table((user_addr_t)((unsigned)name[1]), name[2], name[3]);
	/*
	 * We need to get back into the general MIB, so we need to re-prepend
	 * CTL_VFS to our name and try userland_sysctl().
	 */
	usernamelen = namelen + 1;
	MALLOC(username, int *, usernamelen * sizeof(*username),
	    M_TEMP, M_WAITOK);
	bcopy(name, username + 1, namelen * sizeof(*name));
	username[0] = CTL_VFS;
	error = userland_sysctl(p, username, usernamelen, oldp, 
	                        oldlenp, newp, newlen, oldlenp);
	FREE(username, M_TEMP);
	return (error);
}
/*
 * Dump vnode list (via sysctl) - defunct
 * use "pstat" instead
 */
/* ARGSUSED */
int
sysctl_vnode
(__unused struct sysctl_oid *oidp, __unused void *arg1, __unused int arg2, __unused struct sysctl_req *req)
{
	return(EINVAL);
}
SYSCTL_PROC(_kern, KERN_VNODE, vnode,
		CTLTYPE_STRUCT | CTLFLAG_RD | CTLFLAG_MASKED | CTLFLAG_LOCKED,
		0, 0, sysctl_vnode, "S,", "");
	struct mount *mp;
	int error;
	/*
	 * Since this only runs when rebooting, it is not interlocked.
	 */
	mount_list_lock();
	while(!TAILQ_EMPTY(&mountlist)) {
		mp = TAILQ_LAST(&mountlist, mntlist);
		mount_list_unlock();
		error = dounmount(mp, MNT_FORCE, 0, vfs_context_current());
		if ((error != 0) && (error != EBUSY)) {
			printf("unmount of %s failed (", mp->mnt_vfsstat.f_mntonname);
			printf("%d)\n", error);
			mount_list_lock();
			TAILQ_REMOVE(&mountlist, mp, mnt_list);
			continue;
		} else if (error == EBUSY) {
			/* If EBUSY is returned,  the unmount was already in progress */
			printf("unmount of %p failed (", mp);
			printf("BUSY)\n");	
		} 
		mount_list_lock();
	mount_list_unlock();

	off_t	ioqueue_depth = 0;
	mp->mnt_maxreadcnt = MAX_UPL_SIZE * PAGE_SIZE;
	mp->mnt_maxwritecnt = MAX_UPL_SIZE * PAGE_SIZE;
	if (features & DK_FEATURE_UNMAP)
	
    
			} else {
    
			} else {

	kn->kn_flags |= EV_CLEAR;
sysctl_vfs_noremotehang(__unused struct sysctl_oid *oidp,
		__unused void *arg1, __unused int arg2, struct sysctl_req *req)
	int out, error;
	pid_t pid;
	proc_t p;
	/* We need a pid. */
	if (req->newptr == USER_ADDR_NULL)
		return (EINVAL);
	error = SYSCTL_IN(req, &pid, sizeof(pid));
	if (error)
		return (error);
SYSCTL_PROC(_vfs_generic, OID_AUTO, vfsidlist, CTLFLAG_RD | CTLFLAG_LOCKED,
	
	
		if (want_vp && vnode_on_reliable_media(vp) == FALSE) {
			if ( !LIST_EMPTY(&vp->v_nclinks) || !LIST_EMPTY(&vp->v_ncchildren))


#if CONFIG_VFS_FUNNEL
        struct unsafe_fsnode *l_unsafefs = 0;
#endif /* CONFIG_VFS_FUNNEL */
			"%d free, %d dead, %d rage\n",
		        desiredvnodes, numvnodes, freevnodes, deadvnodes, ragevnodes);
		if (memorystatus_kill_top_proc(TRUE, kMemorystatusFlagsKilledVnodes) < 0) {
#if CONFIG_VFS_FUNNEL
	if (vp->v_unsafefs) {
	        l_unsafefs = vp->v_unsafefs;
		vp->v_unsafefs = (struct unsafe_fsnode *)NULL;
	}
#endif /* CONFIG_VFS_FUNNEL */

#if CONFIG_VFS_FUNNEL
	if (l_unsafefs) {
	        lck_mtx_destroy(&l_unsafefs->fsnodelock, vnode_lck_grp);
		FREE_ZONE((void *)l_unsafefs, sizeof(struct unsafe_fsnode), M_UNSAFEFS);
	}
#endif /* CONFIG_VFS_FUNNEL */

#define UNAGE_THRESHHOLD	25
		 * In some situations, we want to get an iocount
		 * even if the vnode is draining to prevent deadlock,
		 * e.g. if we're in the filesystem, potentially holding
		 * resources that could prevent other iocounts from
		 * being released.
		if (beatdrain && (vp->v_lflag & VL_DRAIN)) {
			break;
			msleep(&vp->v_lflag,   &vp->v_lock, PVFS, "vnode getiocount", NULL);
	if (((vflags & VNODE_WITHID) != 0) && vid != vp->v_id) {
	if (++vp->v_references >= UNAGE_THRESHHOLD) {
/* USAGE:
 * The following api creates a vnode and associates all the parameter specified in vnode_fsparam
 * structure and returns a vnode handle with a reference. device aliasing is handled here so checkalias
 * is obsoleted by this.
 */
int  
vnode_create(uint32_t flavor, uint32_t size, void *data, vnode_t *vpp)
	if (param == NULL)
		return (EINVAL);
	/* Do quick sanity check on the parameters */
	if (param->vnfs_vtype == VBAD) {
		return (EINVAL);
	}
	if ((flavor == VNCREATE_TRIGGER) && (size == VNCREATE_TRIGGER_SIZE)) {
		tinfo = (struct vnode_trigger_param *)data;
		/* Validate trigger vnode input */
		if ((param->vnfs_vtype != VDIR) ||
		    (tinfo->vnt_resolve_func == NULL) ||
		    (tinfo->vnt_flags & ~VNT_VALID_MASK)) {
			return (EINVAL);
		/* Fall through a normal create (params will be the same) */
		flavor = VNCREATE_FLAVOR;
		size = VCREATESIZE;
#endif
	if ((flavor != VNCREATE_FLAVOR) || (size != VCREATESIZE))
		return (EINVAL);

	if ( (error = new_vnode(&vp)) )
		return(error);
			vp->v_mount = NULL;
			vp->v_op = dead_vnodeop_p;
			vp->v_tag = VT_NON;
			vp->v_data = NULL;
			vp->v_type = VBAD;
			vp->v_lflag |= VL_DEAD;
			vp->v_mount = NULL;
			vp->v_op = dead_vnodeop_p;
			vp->v_tag = VT_NON;
			vp->v_data = NULL;
			vp->v_type = VBAD;
			vp->v_lflag |= VL_DEAD;
			if (maj < (u_int)nchrdev &&
			    (D_TYPEMASK & cdevsw[maj].d_type) == D_TTY)
#if CONFIG_VFS_FUNNEL
		if ((param->vnfs_mp->mnt_vtable->vfc_vfsflags & VFC_VFSTHREADSAFE) == 0) {
			MALLOC_ZONE(vp->v_unsafefs, struct unsafe_fsnode *,
				    sizeof(struct unsafe_fsnode), M_UNSAFEFS, M_WAITOK);
			vp->v_unsafefs->fsnode_count = 0;
			vp->v_unsafefs->fsnodeowner  = (void *)NULL;
			lck_mtx_init(&vp->v_unsafefs->fsnodelock, vnode_lck_grp, vnode_lck_attr);
		}
#endif /* CONFIG_VFS_FUNNEL */
		mount_iterdrop(mp);

	if ((error = vfs_getattr(mp, &va, ctx)) != 0) {
		KAUTH_DEBUG("STAT - filesystem returned error %d", error);
		return(error);
	}

	if (ctx == NULL) {		/* XXX technically an error */
		ctx = vfs_context_current();
	if (flags & VNODE_LOOKUP_DOWHITEOUT)
		ndflags |= DOWHITEOUT;
	if (lflags & VNODE_LOOKUP_DOWHITEOUT)
		ndflags |= DOWHITEOUT;
		return VNOP_COMPOUND_OPEN(dvp, vpp, ndp, VNOP_COMPOUND_OPEN_DO_CREATE, fmode, statusp, vap, ctx);
			!(vp->v_mount->mnt_vtable->vfc_vfsflags & VFC_VFSDIRLINKS)) {


			error = vnode_verifynamedstream(vp, ctx);
	
int 
             struct vnode *tdvp,  struct vnode *tvp,  struct componentname *tcnp,
             vfs_context_t ctx, void *reserved)
	error = mac_vnode_check_rename_from(ctx, fdvp, fvp, fcnp);
	if (error)
		goto out;
#endif

#if CONFIG_MACF
	error = mac_vnode_check_rename_to(ctx,
			tdvp, tvp, fdvp == tdvp, tcnp);
		if (fvp->v_type == VDIR && tvp->v_type != VDIR) {
			error = ENOTDIR;
			goto out;
		} else if (fvp->v_type != VDIR && tvp->v_type == VDIR) {
			error = EISDIR;
			goto out;
	error = 0;
	if ((tvp != NULL) && vnode_isdir(tvp)) {
		if (tvp != fdvp)
			moving = 1;
	} else if (tdvp != fdvp) {
		moving = 1;
	}

	/*
	 * must have delete rights to remove the old name even in
	 * the simple case of fdvp == tdvp.
	 *
	 * If fvp is a directory, and we are changing it's parent,
	 * then we also need rights to rewrite its ".." entry as well.
	 */
	if (vnode_isdir(fvp)) {
		if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE | KAUTH_VNODE_ADD_SUBDIRECTORY, ctx)) != 0)
	} else {
		if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE, ctx)) != 0)
	}
	if (moving) {
		/* moving into tdvp or tvp, must have rights to add */
		if ((error = vnode_authorize(((tvp != NULL) && vnode_isdir(tvp)) ? tvp : tdvp,
						NULL, 
						vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE,
						ctx)) != 0) {
	} else {
		/* node staying in same directory, must be allowed to add new name */
		if ((error = vnode_authorize(fdvp, NULL,
						vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE, ctx)) != 0)
	}
	/* overwriting tvp */
	if ((tvp != NULL) && !vnode_isdir(tvp) &&
			((error = vnode_authorize(tvp, tdvp, KAUTH_VNODE_DELETE, ctx)) != 0)) {
		goto out;

 * Deletion is not permitted if the directory is sticky and the caller is
 * not owner of the node or directory.
 * If either the node grants DELETE, or the directory grants DELETE_CHILD,
 * the node may be deleted.  If neither denies the permission, and the
 * caller has Posix write access to the directory, then the node may be
 * deleted.
 * on directories without the sticky bit set.
int
vnode_authorize_delete(vauth_ctx vcp, boolean_t cached_delete_child);
/*static*/ int
	kauth_cred_t		cred = vcp->ctx->vc_ucred;
	struct kauth_acl_eval	eval;
	int			error, delete_denied, delete_child_denied, ismember;
	delete_child_denied = 0;
	if (!cached_delete_child && VATTR_IS_NOT(dvap, va_acl, NULL)) {
			return(error);
			delete_child_denied = 1;
			break;
			/* FALLSTHROUGH */
                case KAUTH_RESULT_ALLOW:
                        KAUTH_DEBUG("%p    ALLOWED - granted by directory ACL", vcp->vp);
                        return(0);
			/* Effectively the same as !delete_child_denied */
	/* check the ACL on the node */
	delete_denied = 0;
	if (VATTR_IS_NOT(vap, va_acl, NULL)) {
		eval.ae_requested = KAUTH_VNODE_DELETE;
		eval.ae_acl = &vap->va_acl->acl_ace[0];
		eval.ae_count = vap->va_acl->acl_entrycount;
		eval.ae_options = 0;
		if (vauth_file_owner(vcp))
			eval.ae_options |= KAUTH_AEVAL_IS_OWNER;
		 * We use ENOENT as a marker to indicate we could not get
		 * information in order to delay evaluation until after we
		 * have the ACL evaluation answer.  Previously, we would
		 * always deny the operation at this point.
		if ((error = vauth_file_ingroup(vcp, &ismember, ENOENT)) != 0 && error != ENOENT)
			return(error);
		if (error == ENOENT)
			eval.ae_options |= KAUTH_AEVAL_IN_GROUP_UNKNOWN;
		else if (ismember)
			eval.ae_options |= KAUTH_AEVAL_IN_GROUP;
		eval.ae_exp_gall = KAUTH_VNODE_GENERIC_ALL_BITS;
		eval.ae_exp_gread = KAUTH_VNODE_GENERIC_READ_BITS;
		eval.ae_exp_gwrite = KAUTH_VNODE_GENERIC_WRITE_BITS;
		eval.ae_exp_gexec = KAUTH_VNODE_GENERIC_EXECUTE_BITS;

		if ((error = kauth_acl_evaluate(cred, &eval)) != 0) {
			KAUTH_DEBUG("%p    ERROR during ACL processing - %d", vcp->vp, error);
			return(error);
		}

		switch(eval.ae_result) {
		case KAUTH_RESULT_DENY:
			delete_denied = 1;
			break;
		case KAUTH_RESULT_ALLOW:
			KAUTH_DEBUG("%p    ALLOWED - granted by file ACL", vcp->vp);
			return(0);
		case KAUTH_RESULT_DEFER:
		default:
			/* Effectively the same as !delete_child_denied */
			KAUTH_DEBUG("%p    DEFERRED%s - by file ACL", vcp->vp, delete_denied ? "(DENY)" : "");
			break;
	/* if denied by ACL on directory or node, return denial */
	if (delete_denied || delete_child_denied) {
		KAUTH_DEBUG("%p    DENIED - denied by ACL", vcp->vp);
		return(EACCES);
	}

		return(EACCES);
	}

	/* check the directory */
	if (!cached_delete_child && (error = vnode_authorize_posix(vcp, VWRITE, 1 /* on_dir */)) != 0) {
		KAUTH_DEBUG("%p    DENIED - denied by posix permisssions", vcp->vp);
		return(error);
	return(0);
	 * Get vnode attributes and extended security information for the vnode
	 * and directory if required.
	 */
	VATTR_WANTED(&va, va_mode);
	VATTR_WANTED(&va, va_uid);
	VATTR_WANTED(&va, va_gid);
	VATTR_WANTED(&va, va_flags);
	VATTR_WANTED(&va, va_acl);
	if ((result = vnode_getattr(vp, &va, ctx)) != 0) {
		KAUTH_DEBUG("%p    ERROR - failed to get vnode attributes - %d", vp, result);
		goto out;
	}
	if (dvp) {
		VATTR_WANTED(&dva, va_mode);
		VATTR_WANTED(&dva, va_uid);
		VATTR_WANTED(&dva, va_gid);
		VATTR_WANTED(&dva, va_flags);
		VATTR_WANTED(&dva, va_acl);
		if ((result = vnode_getattr(dvp, &dva, ctx)) != 0) {
			KAUTH_DEBUG("%p    ERROR - failed to get directory vnode attributes - %d", vp, result);
			goto out;
		}
	}

	/*
	 * If the vnode is an extended attribute data vnode (eg. a resource fork), *_DATA becomes
	 * *_EXTATTRIBUTES.
	 * Point 'vp' to the resource fork's parent for ACL checking
	if (vnode_isnamedstream(vp) &&
	    (vp->v_parent != NULL) &&
	    (vget_internal(vp->v_parent, 0, VNODE_NODEAD | VNODE_DRAINO) == 0)) {
		parent_ref = TRUE;
		vcp->vp = vp = vp->v_parent;
		if (VATTR_IS_SUPPORTED(&va, va_acl) && (va.va_acl != NULL))
			kauth_acl_free(va.va_acl);
		VATTR_INIT(&va);
		VATTR_WANTED(&va, va_mode);
		VATTR_WANTED(&va, va_flags);
		if ((result = vnode_getattr(vp, &va, ctx)) != 0)
	if (!vfs_context_issuser(ctx)) {
	if ((rights & KAUTH_VNODE_DELETE) && parent_authorized_for_delete_child == FALSE) {
	        /*
		 * parent was successfully and newly authorized for content deletions
		 * add it to the cache, but only if it doesn't have the sticky
		 * bit set on it.  This same  check is done earlier guarding
		 * fetching of dva, and if we jumped to out without having done
		 * this, we will have returned already because of a non-zero
		 * 'result' value.
		 */
		if (VATTR_IS_SUPPORTED(&dva, va_mode) &&
		    !(dva.va_mode & (S_ISVTX))) {
		    	/* OK to cache delete rights */
			KAUTH_DEBUG("%p - caching DELETE_CHILD rights", dvp);
			vnode_cache_authorized_action(dvp, ctx, KAUTH_VNODE_DELETE_CHILD);
		}
	}
	int		has_priv_suser, ismember, defaulted_owner, defaulted_group, defaulted_mode;
			struct vnode_attr dva;
			VATTR_INIT(&dva);
			VATTR_WANTED(&dva, va_gid);
			if ((error = vnode_getattr(dvp, &dva, ctx)) != 0)
				goto out;
	
		/* size is meaningless on a directory, don't permit this */
		if (vnode_isdir(vp)) {
			KAUTH_DEBUG("ATTR - ERROR: size change requested on a directory");
			error = EISDIR;
			/* clear set-uid and set-gid bits as required by Posix */
			if (VATTR_IS_ACTIVE(vap, va_mode)) {
				newmode = vap->va_mode;
			} else if (VATTR_IS_SUPPORTED(&ova, va_mode)) {
				newmode = ova.va_mode;
			} else {
				KAUTH_DEBUG("CHOWN - trying to change owner but cannot get mode from filesystem to mask setugid bits");
				newmode = 0;
			}
			if (newmode & (S_ISUID | S_ISGID)) {
				VATTR_SET(vap, va_mode, newmode & ~(S_ISUID | S_ISGID));
				KAUTH_DEBUG("CHOWN - masking setugid bits from mode %o to %o", newmode, vap->va_mode);
vfs_setunmountpreflight(mount_t mp)
	mp->mnt_kern_flag |= MNTK_UNMOUNT_PREFLIGHT;
vfs_setcompoundopen(mount_t mp)
	mount_lock_spin(mp);
	mp->mnt_compound_ops |= COMPOUND_VNOP_OPEN;
	mount_unlock(mp);
/*
 * XXX - get "don't trigger mounts" flag for thread; used by autofs.
 */
extern int thread_notrigger(void);

int
thread_notrigger(void)
{
	struct uthread *uth = (struct uthread *)get_bsdthread_info(current_thread());
	return (uth->uu_notrigger);
}

	char *rbuf = NULL, *cpos, *cend;
	struct nameidata nd_temp;
		goto outsc;
		cpos = rbuf;
		cend = rbuf + siz;
		dp = (struct dirent*) cpos;
		if (cpos == cend)
		while ((cpos < cend)) {
			cpos += dp->d_reclen;
			dp = (struct dirent*)cpos;
		cpos = rbuf;
		cend = rbuf + siz;
		dp = (struct dirent*) cpos;
		if (cpos == cend)
		while ((cpos < cend)) {
				NDINIT(&nd_temp, DELETE, OP_UNLINK, USEDVP,
				       UIO_SYSSPACE, CAST_USER_ADDR_T(dp->d_name),
				       ctx);
				nd_temp.ni_dvp = vp;
				error = unlink1(ctx, &nd_temp, VNODE_REMOVE_SKIP_NAMESPACE_EVENT);
			cpos += dp->d_reclen;
			dp = (struct dirent*)cpos;
	uio_free(auio);
/*
 * Pathname operations that don't trigger a mount for trigger vnodes
 */
static const u_int64_t ignorable_pathops_mask =
	1LL << OP_MOUNT |
	1LL << OP_UNMOUNT |
	1LL << OP_STATFS |
	1LL << OP_ACCESS |
	1LL << OP_GETATTR |
	1LL << OP_LISTXATTR;

int
vfs_istraditionaltrigger(enum path_operation op, const struct componentname *cnp)
{
	if (cnp->cn_flags & ISLASTCN)
		return ((1LL << op) & ignorable_pathops_mask) == 0;
	else
		return (1);
}
